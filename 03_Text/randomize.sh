#!/bin/sh
# 03_Text/randomize.sh — POSIX, без awk, случайность через /dev/urandom + od
# Использование:
#   cat art.txt | ./randomize.sh
#   cat art.txt | ./randomize.sh 0.01

delay="${1:-0}"

# ---- читаем stdin, сохраняя пробелы/бэкслэши ----
lines_tmp="$(mktemp)"; trap 'rm -f "$lines_tmp" "$rowsf" "$colsf" "$charsf" "$idxf" "$randf" "$permf"; printf "\033[?25h"; printf "\033[%s;1H\n" $((last_row + 1))' EXIT
cat > "$lines_tmp"

# ---- временные файлы для координат и символов ----
rowsf="$(mktemp)"
colsf="$(mktemp)"
charsf="$(mktemp)"

# ---- разбираем в (row, col, char), 1-индексация терминала ----
r=0
while IFS= read -r line || [ -n "$line" ]; do
  r=$((r + 1))
  # длина в байтах (ASCII)
  len=$(printf %s "$line" | wc -c | tr -d ' ')
  c=1
  while [ $c -le "$len" ]; do
    ch=$(printf %s "$line" | cut -c "$c")
    printf '%s\n' "$r" >> "$rowsf"
    printf '%s\n' "$c" >> "$colsf"
    printf '%s\n' "$ch" >> "$charsf"
    c=$((c + 1))
  done
done < "$lines_tmp"
last_row=$r

count=$(wc -l < "$rowsf" | tr -d ' ')
[ "$count" -eq 0 ] && exit 0

# ---- список индексов 1..count ----
idxf="$(mktemp)"
i=1
while [ $i -le "$count" ]; do
  echo "$i" >> "$idxf"
  i=$((i + 1))
done

# ---- генерим count случайных 32-бит чисел без awk ----
# od выдаёт пачками: нормализуем в "одно число на строку"
randf="$(mktemp)"
bytes=$((count * 4))
# BSD/macOS od понимает: -An -tu4 -N <bytes>
od -An -tu4 -N "$bytes" /dev/urandom \
  | tr ' ' '\n' | grep '^[0-9][0-9]*$' | head -n "$count" > "$randf"

# ---- делаем случайную перестановку: сортируем индексы по случайным ключам ----
permf="$(mktemp)"
paste "$randf" "$idxf" | sort -n | cut -f2 > "$permf"

# ---- управление терминалом ----
# очистить экран, в (1,1), скрыть курсор
printf '\033[2J\033[H\033[?25l'

# ---- выводим символы в случайном порядке по СВОИМ координатам ----
while IFS= read -r idx; do
  r=$(sed -n "${idx}p" "$rowsf")
  c=$(sed -n "${idx}p" "$colsf")
  ch=$(sed -n "${idx}p" "$charsf")
  printf '\033[%s;%sH%s' "$r" "$c" "$ch"
  # задержка (вещественная допускается; 0 — без задержки)
  if [ "$delay" != "0" ] && [ "$delay" != "0.0" ]; then
    sleep "$delay"
  fi
done < "$permf"

