section .note.GNU-stack noalloc noexec nowrite progbits

section .text
GLOBAL ft_strlen;
ft_strlen:
	mov rax, 0
	jmp L1
L2:
	inc rax
L1:
	cmp byte [rdi + rax], 0
	jne L2
	ret


