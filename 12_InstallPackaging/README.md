# hello-greet — финальный проект (Autotools + libtool + gettext + tests + man + doxygen)

Проект ставит цель показать полный “невырожденный” цикл:
- Autotools/libtool (адаптация к окружению, сборка)
- динамическая библиотека `libgreet`
- программа `hello-greet`, использующая библиотеку
- переводы (gettext), две локали: английская (msgid) и русская (ru)
- unit-тесты (`make check`)
- manpage (`man hello-greet`)
- документация из исходников (Doxygen) + описание проекта
- установка/деинсталляция (в т.ч. от root)

## Зависимости
- autoconf, automake, libtool
- gettext (нужен autopoint)
- компилятор C (gcc/clang)
- doxygen (для `make doc`, необязательно для сборки)
- man-db/mandoc (для просмотра man)

## Сборка из исходников
```bash
autoreconf -fi
./configure
make
make check
