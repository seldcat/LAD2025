#!/bin/sh
set -eu

SCRIPT_DIR=$(dirname "$0")
cd "$SCRIPT_DIR"

FAIL=0

for t in t*.sh; do
    echo "==== Running $t ===="
    if sh "./$t"; then
        echo "$t: OK"
    else
        echo "$t: FAIL"
        FAIL=1
    fi
    echo
done

exit "$FAIL"
