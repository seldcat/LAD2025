#!/bin/sh
set -eu

cd "$(dirname "$0")"

IN="no_such_file.txt"
OUT="outfile_no_such.txt"

rm -f "$IN" "$OUT"

set +e
./../move "$IN" "$OUT"
RC=$?
set -e

if [ "$RC" -ne 2 ]; then
    echo "Expected exit code 2 (ERR_IN_OPEN), got $RC"
    exit 1
fi

if [ -e "$OUT" ]; then
    echo "Output file should not be created when input open fails"
    exit 1
fi

exit 0
