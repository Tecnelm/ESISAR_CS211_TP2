CC = gcc
CFLAGS = -Wall
OUT = out
EXEC = TP2

OBJDIR = obj
SRCDIR = travail_preparatoire
MAINDIR = .

MAIN = main.c
SRCS= $(wildcard $(SRCDIR)/*.c)
OBJS= $(SRCS:$(SRCDIR)/%.c=$(OUT)/$(OBJDIR)/%.o) $(OUT)/$(OBJDIR)/main.o




$(OUT)/$(EXEC):$(OBJS)
	@mkdir -p $(OUT)
	@mkdir -p $(OUT)/$(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OUT)/$(OBJDIR)/main.o: $(MAINDIR)/main.c
	@mkdir -p $(OUT)
	@mkdir -p $(OUT)/$(OBJDIR)
	$(CC) -o $@ -c $^ $(CFLAGS)

$(OUT)/$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OUT)
	@mkdir -p $(OUT)/$(OBJDIR)
	$(CC) -o $@ -c $^ $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf $(OUT)/$(OBJDIR)/*.o

mrproper: clean
	@rm -rf $(OUT)

run: $(OUT)/$(EXEC)
	@./$(OUT)/$(EXEC)
