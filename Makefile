CC = gcc
CFLAGS = -Wall
OUT = out
EXEC = TP2
DEBUG = no
TEST = yes

OBJDIR = obj
SRCDIR = src
MAINDIR = .

MAIN = main

SRCS= $(wildcard $(SRCDIR)/*.c)
OBJS= $(SRCS:$(SRCDIR)/%.c=$(OUT)/$(OBJDIR)/%.o) $(OUT)/$(OBJDIR)/$(MAIN).o
HEADER =$(wildcard $(SRCDIR)/*.h)

ifeq ($(DEBUG),yes)
	CFLAGS := $(CFLAGS) -g
endif
ifeq ($(TEST),yes)
	CFLAGS := $(CFLAGS) -DTEST
endif

$(OUT)/$(EXEC):$(OBJS) $(HEADER)
	@mkdir -p $(OUT)
	@mkdir -p $(OUT)/$(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OUT)/$(OBJDIR)/$(MAIN).o: $(MAINDIR)/$(MAIN).c
	@mkdir -p $(OUT)
	@mkdir -p $(OUT)/$(OBJDIR)
	$(CC) -o $@ -c $^ $(CFLAGS)

$(OUT)/$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	@mkdir -p $(OUT)
	@mkdir -p $(OUT)/$(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper run


clean:
	@rm -rf $(OUT)/$(OBJDIR)/*.o

mrproper: clean
	@rm -rf $(OUT)

run: $(OUT)/$(EXEC)
	@./$(OUT)/$(EXEC)
