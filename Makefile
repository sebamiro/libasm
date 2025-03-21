all:
	nasm -f elf64 ft_strlen.s
	make test
test: test.c ft_strlen.o
	gcc -Wall -Werror -Wextra test.c ft_strlen.o -o test
