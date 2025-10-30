#!/bin/sh
set -eu

cd "$(dirname "$0")"

IN="infile_read_error.txt"
OUT="outfile_read_error.txt"

rm -f "$IN" "$OUT" strace_read.log
printf 'test data\n' > "$IN"

set +e
strace -qq \
  -P "$IN" \
  -e trace=read \
  -e inject=read:error=EIO:when=1 \
  ../move "$IN" "$OUT" > /dev/null 2>strace_read.log
RC=$?
set -e

if [ "$RC" -ne 5 ]; then
    echo "Expected exit code 5 (ERR_READ), got $RC"
    exit 1
fi

if [ ! -e "$IN" ]; then
    echo "Input file should remain after read error"
    exit 1
fi

if [ -e "$OUT" ]; then
    echo "Output file should be removed after read error"
    exit 1
fi

exit 0
