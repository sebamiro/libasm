LibName = libasm.a
TestName = test
TestSrc = test.c
AsmSrc = ft_strlen.s ft_strcpy.s ft_strdup.s ft_strcmp.s ft_write.s ft_read.s
AsmObj = $(AsmSrc:.s=.o)

$(LibName): $(AsmObj)
	ar rcs $@ $(AsmObj)

test: $(TestSrc) $(LibName)
	gcc -no-pie -Wall -Werror -Wextra test.c -o $(TestName) -L. -lasm

%.o: %.s
	nasm -f elf64 $< -o $@

clean:
	rm -rf $(AsmObj) $(TestName) $(LibName)

