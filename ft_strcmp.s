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


