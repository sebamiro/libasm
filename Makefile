AsmSrc = ft_strlen.s ft_strcpy.s ft_strdup.s ft_strcmp.s ft_write.s ft_read.s
AsmObj = $(AsmSrc:.s=.o)

test: test.c $(AsmObj)
	gcc -no-pie -Wall -Werror -Wextra test.c $(AsmObj) -o test

%.o: %.s
	nasm -f elf64 $< -o $@

clean:
	rm -rf $(AsmObj) test

