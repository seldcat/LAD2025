# hello-greet

`hello-greet` is a tiny demo project showing:
- Autotools + libtool build
- shared library `libgreet`
- GNU gettext translations (EN/RU)
- unit tests (`make check`)
- manpage installation
- documentation generation from sources (Doxygen)

## Build

```bash
autoreconf -fi
./configure
make
make check
