TARGET = my_shell
OBJ = my_shell.c parse_input.c builtins.c
CC = gcc

all:
	$(CC) -o $(TARGET) $(OBJ)
clean:
	rm -f -*o
fclean:
	rm -f $(TARGET)
