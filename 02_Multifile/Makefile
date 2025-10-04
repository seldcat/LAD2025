# ========= Конфигурация компиляции =========
CC       := cc
AR       := ar
ARFLAGS  := rcs
CFLAGS   := -Wall -Wextra -O2 -fPIC -MMD -MP
LDFLAGS  :=
# rpath, чтобы prog-so находил liboutput.so в каталоге с бинарём
RPATH_ORIGIN := -Wl,-rpath,'$$ORIGIN'

# ========= Имена артефактов =========
LIBSTATIC := liboutput_static.a
LIBSHARED := liboutput.so

OBJS_LIB  := fun.o const.o
OBJ_PROG  := prog.o

PROG      := prog
PROG_A    := prog-a
PROG_SO   := prog-so

# Папка для файлов вывода тестов
TESTDIR   := tests_out

# Аргументы для тестов (один и три параметра)
ARG1      := one
ARG3      := one two three

# ========= Цель по умолчанию =========
# Собирает 2 библиотеки и 3 бинарника
.PHONY: all
all: $(LIBSTATIC) $(LIBSHARED) $(PROG) $(PROG_A) $(PROG_SO)

# ========= Правила сборки библиотек =========
$(LIBSTATIC): $(OBJS_LIB)
	$(AR) $(ARFLAGS) $@ $^

$(LIBSHARED): $(OBJS_LIB)
	$(CC) -shared -o $@ $^

# ========= Правила сборки бинарников =========
# prog — линковка напрямую из .o (как просили «из .o-файлов»)
$(PROG): $(OBJ_PROG) $(OBJS_LIB)
	$(CC) $^ -o $@

# prog-a — статическая линковка с liboutput_static.a
$(PROG_A): $(OBJ_PROG) $(LIBSTATIC)
	$(CC) $^ -o $@

# prog-so — динамическая линковка с liboutput.so
$(PROG_SO): $(OBJ_PROG) $(LIBSHARED)
	$(CC) $(OBJ_PROG) -L. -loutput $(RPATH_ORIGIN) -o $@

# ========= Компиляция объектов =========
# Общий шаблон: .c -> .o (+ генерация .d)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Явные зависимости от заголовка (если используется)
prog.o fun.o const.o: outlib.h

# ========= Тесты =========
# test: запускает каждый бинарник без аргументов, с 1 и 3 аргументами,
# сравнивает соответствующие выводы между prog, prog-a, prog-so.
.PHONY: test
test: all
	@mkdir -p $(TESTDIR)
	@set -e; \
	for b in $(PROG) $(PROG_A) $(PROG_SO); do \
	  echo "Running $$b (no args)"; \
	  ./$$b > $(TESTDIR)/$$b.noargs.txt 2>&1; \
	  echo "Running $$b (1 arg)"; \
	  ./$$b $(ARG1) > $(TESTDIR)/$$b.one.txt 2>&1; \
	  echo "Running $$b (3 args)"; \
	  ./$$b $(ARG3) > $(TESTDIR)/$$b.three.txt 2>&1; \
	done; \
	echo "Comparing outputs (prog vs prog-a)"; \
	cmp -s $(TESTDIR)/$(PROG).noargs.txt $(TESTDIR)/$(PROG_A).noargs.txt; \
	cmp -s $(TESTDIR)/$(PROG).one.txt    $(TESTDIR)/$(PROG_A).one.txt; \
	cmp -s $(TESTDIR)/$(PROG).three.txt  $(TESTDIR)/$(PROG_A).three.txt; \
	echo "Comparing outputs (prog vs prog-so)"; \
	cmp -s $(TESTDIR)/$(PROG).noargs.txt $(TESTDIR)/$(PROG_SO).noargs.txt; \
	cmp -s $(TESTDIR)/$(PROG).one.txt    $(TESTDIR)/$(PROG_SO).one.txt; \
	cmp -s $(TESTDIR)/$(PROG).three.txt  $(TESTDIR)/$(PROG_SO).three.txt; \
	echo "All tests passed: outputs are identical."

# ========= Уборка =========
.PHONY: clean
clean:
	$(RM) -f $(PROG) $(PROG_A) $(PROG_SO) \
	       $(LIBSTATIC) $(LIBSHARED) \
	       *.o *.d a.out
	$(RM) -rf $(TESTDIR)

# Подтягиваем авто-зависимости компилятора
-include $(wildcard *.d)

