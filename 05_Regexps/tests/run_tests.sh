#!/bin/sh
set -e

echo "Running ESUB test suite"

for t in tests/t*.sh; do
    echo "Running $t"
    sh "$t"
done

echo "All tests OK"
