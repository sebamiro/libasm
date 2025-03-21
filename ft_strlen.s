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

section .text
GLOBAL ft_strcpy;
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

section .text
GLOBAL ft_strcmp;
ft_strcmp:
	xor rax, rax
	jmp L6
L5:
	cmp al, 0
	je L8
	inc rdi
	inc rsi
L6:
	mov al, [rdi]
	mov cl, [rsi]
	sub rax, rcx
	je L5
L8:
	ret

