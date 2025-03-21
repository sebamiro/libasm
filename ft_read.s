section .text
extern __errno_location
global ft_read;
ft_read:
	mov rax, 0 ; read syscall
	syscall
	cmp rax, 0
	jge RET

	neg rax
	mov rdi, rax
	call __errno_location
	mov [rax], rdi
	mov rax, -1
RET:
	ret


