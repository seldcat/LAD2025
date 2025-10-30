#!/bin/sh
echo "hello" | ./esub '(h)(e)(l)(l)(o)' '\\1_\\5' > out
echo "hello" | sed -E 's/(h)(e)(l)(l)(o)/\\1_\\5/' > ref
diff -u ref out
rm out ref
