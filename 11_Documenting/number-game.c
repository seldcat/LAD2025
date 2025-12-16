/**
 * @file number-game.c
 * @brief Interactive number guessing game.
 *
 * Guess a number from 1 to 100 using binary search.
 * Supports Arabic and Roman numerals output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/** Minimum allowed number */
#define MIN_NUM 1
/** Maximum allowed number */
#define MAX_NUM 100

/**
 * Roman numerals table for values 1..100.
 * Index 0 is unused.
 */
static const char *roman_table[MAX_NUM + 1] = {
    NULL,
    "I","II","III","IV","V","VI","VII","VIII","IX","X",
    "XI","XII","XIII","XIV","XV","XVI","XVII","XVIII","XIX","XX",
    "XXI","XXII","XXIII","XXIV","XXV","XXVI","XXVII","XXVIII","XXIX","XXX",
    "XXXI","XXXII","XXXIII","XXXIV","XXXV","XXXVI","XXXVII","XXXVIII","XXXIX","XL",
    "XLI","XLII","XLIII","XLIV","XLV","XLVI","XLVII","XLVIII","XLIX","L",
    "LI","LII","LIII","LIV","LV","LVI","LVII","LVIII","LIX","LX",
    "LXI","LXII","LXIII","LXIV","LXV","LXVI","LXVII","LXVIII","LXIX","LXX",
    "LXXI","LXXII","LXXIII","LXXIV","LXXV","LXXVI","LXXVII","LXXVIII","LXXIX","LXXX",
    "LXXXI","LXXXII","LXXXIII","LXXXIV","LXXXV","LXXXVI","LXXXVII","LXXXVIII","LXXXIX","XC",
    "XCI","XCII","XCIII","XCIV","XCV","XCVI","XCVII","XCVIII","XCIX","C"
};

/**
 * Convert integer to Roman numeral.
 *
 * @param value Integer value (1..100)
 * @return Roman numeral string or NULL on error
 */
const char *int_to_roman(int value) {
    if (value < MIN_NUM || value > MAX_NUM)
        return NULL;
    return roman_table[value];
}

/**
 * Convert Roman numeral to integer.
 *
 * @param roman Roman numeral string
 * @return Integer value or -1 if invalid
 */
int roman_to_int(const char *roman) {
    for (int i = MIN_NUM; i <= MAX_NUM; i++) {
        if (strcmp(roman_table[i], roman) == 0)
            return i;
    }
    return -1;
}

/* ---------- help output ---------- */

static void print_help_en(void) {
    puts("Number Guessing Game — guess a number from 1 to 100\n");
    puts("Usage:");
    puts("  number-game [OPTIONS]\n");
    puts("Options:");
    puts("  -r          Use Roman numerals");
    puts("  --help      Show this help and exit");
    puts("  --help-md   Print help in Markdown format");
}

static void print_help_ru(void) {
    puts("Игра угадывания чисел — загадайте число от 1 до 100\n");
    puts("Использование:");
    puts("  number-game [ОПЦИИ]\n");
    puts("Опции:");
    puts("  -r          Использовать римские цифры");
    puts("  --help      Показать эту справку и выйти");
    puts("  --help-md   Вывести справку в формате Markdown");
}

static void print_help_md(void) {
    puts("# Number Guessing Game");
    puts("");
    puts("Guess a number from **1 to 100** using binary search.");
    puts("");
    puts("## Usage");
    puts("");
    puts("```");
    puts("number-game [OPTIONS]");
    puts("```");
    puts("");
    puts("## Options");
    puts("");
    puts("- `-r` — use Roman numerals");
    puts("- `--help` — show help");
    puts("- `--help-md` — print this help in Markdown");
}

/* ---------- main ---------- */

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");

    int use_roman = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            use_roman = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_help_en();
            puts("");
            print_help_ru();
            return 0;
        } else if (strcmp(argv[i], "--help-md") == 0) {
            print_help_md();
            return 0;
        }
    }

    int low = MIN_NUM;
    int high = MAX_NUM;
    char buf[32];

    puts("Think of a number.");

    while (low < high) {
        int mid = (low + high) / 2;

        if (use_roman)
            printf("Is your number greater than %s? (Yes/No): ",
                   int_to_roman(mid));
        else
            printf("Is your number greater than %d? (Yes/No): ", mid);

        if (!fgets(buf, sizeof(buf), stdin)) {
            fprintf(stderr, "EOF error\n");
            return 1;
        }

        if (strncmp(buf, "Yes", 3) == 0)
            low = mid + 1;
        else if (strncmp(buf, "No", 2) == 0)
            high = mid;
        else
            puts("Please answer Yes or No.");
    }

    if (use_roman)
        printf("Your number is %s\n", int_to_roman(low));
    else
        printf("Your number is %d\n", low);

    return 0;
}
