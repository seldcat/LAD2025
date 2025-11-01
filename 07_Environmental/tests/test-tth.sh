#!/bin/sh
set -e

echo "abc" > f_tth

out=$(
  printf "Tth f_tth\n" |
  rhasher 2>/dev/null |
  sed '/^rhasher>/d' |
  tail -n 1
)

ref=$(rhash --tth --hex f_tth | awk '{print $1}')

if [ "$out" != "$ref" ]; then
  echo "TTH mismatch"
  echo "expected: $ref"
  echo "got:      $out"
  exit 1
fi
