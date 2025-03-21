global ft_strcpy;
section .text
ft_strcpy:
	mov rax, 0
	jmp L4
L3:
	inc rax
L4:
	mov dl, [rsi + rax]
	mov [rdi + rax], dl
	cmp byte [rdi + rax], 0
	jne L3

	mov rax, rdi
	ret

