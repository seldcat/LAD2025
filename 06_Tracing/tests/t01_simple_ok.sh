#!/bin/sh
set -eu

cd "$(dirname "$0")"

INFILE="infile_simple.txt"
OUTFILE="outfile_simple.txt"

rm -f "$INFILE" "$OUTFILE"

echo "hello world" > "$INFILE"

./../move "$INFILE" "$OUTFILE"
RC=$?

[ "$RC" -eq 0 ] || {
    echo "Expected exit code 0, got $RC"
    exit 1
}

if [ -e "$INFILE" ]; then
    echo "Input file still exists after successful move"
    exit 1
fi

if [ ! -e "$OUTFILE" ]; then
    echo "Output file does not exist after successful move"
    exit 1
fi

CONTENT="$(cat "$OUTFILE")"
if [ "$CONTENT" != "hello world" ]; then
    echo "Unexpected output content: '$CONTENT'"
    exit 1
fi

exit 0
