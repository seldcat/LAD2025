#!/bin/sh
echo "foo123bar" | ./esub '([a-z]+)([0-9]+)' '\2-\1' > out
echo "foo123bar" | sed -E 's/([a-z]+)([0-9]+)/\2-\1/' > ref
diff -u ref out
rm out ref
