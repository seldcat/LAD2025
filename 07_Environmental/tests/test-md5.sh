
#!/bin/sh
set -e

echo "test" > f_md5

out=$(
  printf "Md5 f_md5\n" |
  rhasher 2>/dev/null |
  sed '/^rhasher>/d' |
  tail -n 1
)

ref=$(md5sum f_md5 | awk '{print $1}')

if [ "$out" != "$ref" ]; then
  echo "MD5 mismatch"
  echo "expected: $ref"
  echo "got:      $out"
  exit 1
fi
