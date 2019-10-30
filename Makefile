CC = gcc
CFLAGS = -Wall
OUT = out
EXEC = TP2

OBJDIR = obj
SRCDIR = travail_preparatoire
MAINDIR =

MAIN = main.c
SRCS= $(wildcard $(SRCDIR)/*.c)
OBJS= $(SRCS:$(SRCDIR)/%.c=$(OUT)/$(OBJDIR)/%.o)




$(OUT)/$(EXEC):$(OBJS)
	@mkdir -p $(OUT)
	@mkdir -p $(OUT)/$(OBJDIR)
	@echo $(SRCS)
	@echo $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $@


$(OUT)/$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OUT)
	mkdir -p $(OUT)/$(OBJDIR)
	$(CC) -o $@ -c $^ $(CFLAGS)



EXEC=hello
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

hello: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
