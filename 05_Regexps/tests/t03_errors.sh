#!/bin/sh
if ./esub '([a-z]+' 'X' 'abc' 2>err ; then
    echo "ERROR: esub should have failed"
    exit 1
fi
if [ ! -s err ]; then
    echo "ERROR: esub did not print diagnostics"
    exit 1
fi
rm -f err
