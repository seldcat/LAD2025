#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* Чтение одной строки произвольной длины.
 * Возвращает malloc-нутую строку БЕЗ завершающего '\n' (если он был — удаляется).
 * Возвращает NULL на EOF без данных.
 */
static char *read_line_dynamic(FILE *fp) {
    if (!fp) return NULL;

    size_t cap = 256;
    size_t len = 0;
    char *buf = (char*)malloc(cap);
    if (!buf) return NULL;

    int c = 0;
    int got_any = 0;

    while ((c = fgetc(fp)) != EOF) {
        got_any = 1;
        if (c == '\n') break;

        if (len + 1 >= cap) {
            size_t ncap = cap * 2;
            char *nbuf = (char*)realloc(buf, ncap);
            if (!nbuf) {
                free(buf);
                return NULL;
            }
            buf = nbuf;
            cap = ncap;
        }
        buf[len++] = (char)c;
    }

    if (!got_any) { /* EOF и ничего не прочитали */
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    return buf;
}

static const char *basename_simple(const char *path) {
    if (!path) return "";
    const char *slash = strrchr(path, '/');
#ifdef _WIN32
    const char *bslash = strrchr(path, '\\');
    if (!slash || (bslash && bslash > slash)) slash = bslash;
#endif
    return slash ? (slash + 1) : path;
}

static void print_line_truncated(WINDOW *inner, const char *s, int inner_w) {
    if (!s) {
        waddch(inner, '\n');
        return;
    }
    int maxlen = (inner_w > 1) ? (inner_w - 1) : 0;
    if (maxlen > 0) {
        /* waddnstr печатает не более n символов */
        waddnstr(inner, s, maxlen);
    }
    waddch(inner, '\n');
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filepath = argv[1];
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open '%s': %s\n", filepath, strerror(errno));
        return EXIT_FAILURE;
    }

    /* --- ncurses init --- */
    initscr();
    cbreak();             /* немедленная обработка клавиш */
    noecho();             /* не печатать нажатые символы */
    keypad(stdscr, TRUE); /* на всякий случай, хотя нужны только SPACE/ESC */
    curs_set(0);          /* курсор убираем для аккуратности */

    int H = LINES;
    int W = COLS;

    box(stdscr, 0, 0);
    const char *fname = basename_simple(filepath);
    {
        int max_title = (W > 6) ? (W - 6) : 0; /* запас на пробелы и [] */
        char titlebuf[1024];
        snprintf(titlebuf, sizeof(titlebuf), "[ %s ]", fname);
        if ((int)strlen(titlebuf) > max_title && max_title > 0) {
            char tmp[1024];
            strncpy(tmp, titlebuf, (size_t)max_title);
            tmp[max_title] = '\0';
            mvwprintw(stdscr, 0, 2, "%s", tmp);
        } else {
            mvwprintw(stdscr, 0, 2, "%s", titlebuf);
        }
    }

    int inner_h = (H >= 2) ? (H - 2) : 0;
    int inner_w = (W >= 2) ? (W - 2) : 0;
    WINDOW *inner = NULL;
    if (inner_h > 0 && inner_w > 0) {
        inner = derwin(stdscr, inner_h, inner_w, 1, 1);
    } else {
        mvwprintw(stdscr, 1, 1, "Terminal too small.");
        wrefresh(stdscr);
        getch();
        endwin();
        fclose(fp);
        return EXIT_FAILURE;
    }

    scrollok(inner, TRUE);

    wrefresh(stdscr);
    wrefresh(inner);

    int lines_drawn = 0;
    int ch = 0;
    int eof_reached = 0;

    while (lines_drawn < inner_h) {
        char *line = read_line_dynamic(fp);
        if (!line) { /* EOF */
            eof_reached = 1;
            break;
        }
        print_line_truncated(inner, line, inner_w);
        free(line);
        lines_drawn++;
    }

    wrefresh(inner);

    while ((ch = getch()) != 27) { /* 27 == ESC */
        if (ch == ' ') {
            if (!eof_reached) {
                char *line = read_line_dynamic(fp);
                if (!line) {
                    eof_reached = 1;
                } else {
                    print_line_truncated(inner, line, inner_w);
                    free(line);
                }
                wrefresh(inner);
            }
        }
    }

    delwin(inner);
    endwin();
    fclose(fp);
    return EXIT_SUCCESS;
}

