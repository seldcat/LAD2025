#!/bin/sh
set -eu

cd "$(dirname "$0")"

IN="PROTECT_input.txt"
OUT="regular_output.txt"

rm -f "$IN" "$OUT" protect.log

echo "secret data" > "$IN"

LIB="$(realpath ../libprotect.so)"

set +e
LD_PRELOAD="$LIB" ../move "$IN" "$OUT" > /dev/null 2>protect.log
RC=$?
set -e

if [ "$RC" -ne 10 ]; then
    echo "Expected exit code 10 (ERR_UNLINK_IN), got $RC"
    exit 1
fi

if [ ! -e "$IN" ]; then
    echo "Protected input file must remain"
    exit 1
fi

if [ ! -e "$OUT" ]; then
    echo "Output file must be created"
    exit 1
fi

if [ "$(cat "$IN")" != "$(cat "$OUT")" ]; then
    echo "Input and output content must match"
    exit 1
fi

exit 0
