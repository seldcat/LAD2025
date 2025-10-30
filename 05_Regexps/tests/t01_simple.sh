#!/bin/sh
echo "abc123" | ./esub '[a-z]+' 'XXX' > out
echo "abc123" | sed -E 's/[a-z]+/XXX/' > ref
diff -u ref out
rm out ref
