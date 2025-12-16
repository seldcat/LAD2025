/**
 * @file hello-greet.c
 * @brief Command-line utility using libgreet with gettext translations.
 */

#include "config.h"
#include "greet.h"

#include <locale.h>
#include <libintl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef TESTING
#  define _(S) fake_gettext(S)
const char *fake_gettext(const char *s) {
    if (strcmp(s, "Hello") == 0)
        return "Привет";
    if (strcmp(s, "Error: out of memory") == 0)
        return "Ошибка: не хватает памяти";
    return s;
}
#else
#  define _(S) gettext(S)
#endif


#define _(S) gettext(S)

static void print_help_en(FILE *out) {
    fprintf(out,
        "hello-greet — tiny demo app using libgreet\n"
        "\n"
        "Usage:\n"
        "  hello-greet [--help] [NAME]\n"
        "\n"
        "Description:\n"
        "  Prints a localized greeting. If NAME is omitted, uses a default.\n"
        "\n"
        "Environment:\n"
        "  APP_LOCALEDIR  Override locale directory (useful for running from build tree)\n"
        "  LANGUAGE       Standard gettext variable to pick a language\n"
        "\n");
}

static void print_help_ru(FILE *out) {
    fprintf(out,
        "hello-greet — маленькая утилита, использующая libgreet\n"
        "\n"
        "Использование:\n"
        "  hello-greet [--help] [ИМЯ]\n"
        "\n"
        "Описание:\n"
        "  Печатает приветствие с переводом. Если ИМЯ не задано, берётся значение по умолчанию.\n"
        "\n"
        "Окружение:\n"
        "  APP_LOCALEDIR  Переопределить каталог локалей (удобно для запуска из дерева сборки)\n"
        "  LANGUAGE       Стандартная переменная gettext для выбора языка\n"
        "\n");
}

static void i18n_init(void) {
    setlocale(LC_ALL, "");

    const char *override = getenv("APP_LOCALEDIR");
    if (override && override[0]) {
        bindtextdomain(PACKAGE, override);
    } else {
        bindtextdomain(PACKAGE, LOCALEDIR);
    }
    textdomain(PACKAGE);
}

int main(int argc, char **argv) {
    if (argc >= 2 && strcmp(argv[1], "--help") == 0) {
        print_help_en(stdout);
        fputc('\n', stdout);
        print_help_ru(stdout);
        return 0;
    }

    i18n_init();

    const char *name = (argc >= 2) ? argv[1] : NULL;

    const char *prefix = _("Hello");
    char *msg = greet_build(prefix, name);
    if (!msg) {
        fprintf(stderr, "%s\n", _("Error: out of memory"));
        return 2;
    }

    puts(msg);
    free(msg);
    return 0;
}
