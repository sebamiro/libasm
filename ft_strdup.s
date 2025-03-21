GLOBAL ft_strdup;
extern ft_strlen
extern malloc
section .text
ft_strdup:
	call ft_strlen
	mov r8, rdi
	mov rdi, rax
	call malloc
	xor r9, r9
	jmp L10
L9:
	inc r9
L10:
	mov dl, [r8+r9]
	mov [rax+r9], dl
	cmp dl, 0
	jne L9
	ret


