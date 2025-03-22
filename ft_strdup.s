section .note.GNU-stack
global ft_strdup;
extern ft_strlen
extern malloc
section .text
ft_strdup:
	call ft_strlen
	push rdi
	mov rdi, rax
	call malloc
	pop rdi
	xor r9, r9
	jmp L10
L9:
	inc r9
L10:
	mov dl, [rdi+r9]
	mov [rax+r9], dl
	cmp dl, 0
	jne L9
	ret


