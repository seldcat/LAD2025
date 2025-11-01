
#!/bin/sh
set -e

echo "hello" > f_sha1

out=$(
  printf "Sha1 f_sha1\n" |
  rhasher 2>/dev/null |
  sed '/^rhasher>/d' |
  tail -n 1
)

ref=$(sha1sum f_sha1 | awk '{print $1}')

if [ "$out" != "$ref" ]; then
  echo "SHA1 mismatch"
  echo "expected: $ref"
  echo "got:      $out"
  exit 1
fi
