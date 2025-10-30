#!/bin/sh
set -eu

cd "$(dirname "$0")"

IN="infile_write_error.txt"
OUT="outfile_write_error.txt"

rm -f "$IN" "$OUT" strace_write.log

dd if=/dev/zero of="$IN" bs=1024 count=4 >/dev/null 2>&1

set +e
strace -qq -e trace=write -e inject=write:error=ENOSPC:when=1 \
    ./../move "$IN" "$OUT" > /dev/null 2>strace_write.log
RC=$?
set -e

if [ "$RC" -ne 6 ]; then
    echo "Expected exit code 6 (ERR_WRITE), got $RC"
    exit 1
fi

[ -e "$IN" ] || {
    echo "Input file should remain after write error"
    exit 1
}

[ ! -e "$OUT" ] || {
    echo "Output file should be removed after write error"
    exit 1
}

exit 0
