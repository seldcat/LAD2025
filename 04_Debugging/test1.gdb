set pagination off
set confirm off

file ./range

break print_value
commands
  silent
  if (g_current % 5) == 0
    echo @@@
    printf " start=%lld stop=%lld step=%lld current=%lld index=%lld\n", \
           g_start, g_stop, g_step, g_current, g_index
  end
  continue
end

run 1 12 > /dev/null
