	.file	"main.c"
	.text
.Ltext0:
	.globl	winW
	.data
	.align 4
	.type	winW, @object
	.size	winW, 4
winW:
	.long	1280
	.globl	winH
	.align 4
	.type	winH, @object
	.size	winH, 4
winH:
	.long	960
	.globl	pointer_x
	.bss
	.align 8
	.type	pointer_x, @object
	.size	pointer_x, 8
pointer_x:
	.zero	8
	.globl	pointer_y
	.align 8
	.type	pointer_y, @object
	.size	pointer_y, 8
pointer_y:
	.zero	8
	.comm	objX,8,8
	.comm	objY,8,8
	.comm	objZ,8,8
	.globl	cam_height
	.data
	.align 8
	.type	cam_height, @object
	.size	cam_height, 8
cam_height:
	.long	0
	.long	1075052544
	.globl	cam_angle
	.bss
	.align 8
	.type	cam_angle, @object
	.size	cam_angle, 8
cam_angle:
	.zero	8
	.globl	mode_name
	.section	.rodata
.LC0:
	.string	"WATCH"
.LC1:
	.string	"BREED"
.LC2:
	.string	"CARRY"
.LC3:
	.string	"COLOR"
.LC4:
	.string	"LINE"
	.section	.data.rel.local,"aw",@progbits
	.align 32
	.type	mode_name, @object
	.size	mode_name, 40
mode_name:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.globl	mode
	.bss
	.align 4
	.type	mode, @object
	.size	mode, 4
mode:
	.zero	4
	.globl	rgb_flg
	.align 4
	.type	rgb_flg, @object
	.size	rgb_flg, 4
rgb_flg:
	.zero	4
	.globl	rgb_pm
	.data
	.align 4
	.type	rgb_pm, @object
	.size	rgb_pm, 4
rgb_pm:
	.long	1
	.comm	line_flg,4,4
	.text
	.globl	init
	.type	init, @function
init:
.LFB5:
	.file 1 "main.c"
	.loc 1 53 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	.loc 1 54 0
	movl	$0, %edi
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	.loc 1 55 0
	movl	$10, %edi
	call	initCat@PLT
	.loc 1 56 0
	call	texinit@PLT
	.loc 1 57 0
	leaq	camera(%rip), %rdi
	call	unitMat@PLT
	.loc 1 58 0
	call	makeCloud@PLT
	.loc 1 59 0
	movl	$0, %eax
	call	makeBucket@PLT
	.loc 1 60 0
	movl	$-1, pick_obj(%rip)
	.loc 1 61 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	init, .-init
	.globl	shaking
	.type	shaking, @function
shaking:
.LFB6:
	.loc 1 63 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$176, %rsp
	.loc 1 63 0
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 66 0
	movsd	.LC5(%rip), %xmm0
	movsd	%xmm0, -88(%rbp)
	.loc 1 67 0
	movl	count.18428(%rip), %eax
	cmpl	$5, %eax
	jg	.L3
	.loc 1 68 0
	movsd	-88(%rbp), %xmm1
	movq	.LC6(%rip), %xmm0
	xorpd	%xmm1, %xmm0
	movsd	%xmm0, -88(%rbp)
.L3:
	.loc 1 69 0
	leaq	-160(%rbp), %rax
	movq	-88(%rbp), %rdx
	pxor	%xmm2, %xmm2
	pxor	%xmm1, %xmm1
	movq	%rdx, -168(%rbp)
	movsd	-168(%rbp), %xmm0
	movq	%rax, %rdi
	call	tlMat@PLT
	movq	-160(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-128(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	.loc 1 70 0
	leaq	-80(%rbp), %rax
	leaq	camera(%rip), %rsi
	movq	%rax, %rdi
	call	dotMat@PLT
	.loc 1 71 0
	leaq	-80(%rbp), %rax
	movq	%rax, %rsi
	leaq	camera(%rip), %rdi
	call	copyMat@PLT
	.loc 1 72 0
	leaq	inv(%rip), %rsi
	leaq	camera(%rip), %rdi
	call	gluInvertMatrix@PLT
	.loc 1 73 0
	movl	count.18428(%rip), %eax
	addl	$1, %eax
	movl	%eax, count.18428(%rip)
	.loc 1 74 0
	movl	count.18428(%rip), %eax
	cmpl	$12, %eax
	jne	.L6
	.loc 1 75 0
	movl	$0, count.18428(%rip)
.L6:
	.loc 1 76 0
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	shaking, .-shaking
	.globl	getWorldCood
	.type	getWorldCood, @function
getWorldCood:
.LFB7:
	.loc 1 79 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$320, %rsp
	movl	%edi, -308(%rbp)
	movl	%esi, -312(%rbp)
	.loc 1 79 0
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 81 0
	leaq	-272(%rbp), %rax
	movq	%rax, %rsi
	movl	$2982, %edi
	call	glGetDoublev@PLT
	.loc 1 84 0
	leaq	-144(%rbp), %rax
	movq	%rax, %rsi
	movl	$2983, %edi
	call	glGetDoublev@PLT
	.loc 1 87 0
	leaq	-288(%rbp), %rax
	movq	%rax, %rsi
	movl	$2978, %edi
	call	glGetIntegerv@PLT
	.loc 1 91 0
	movl	winH(%rip), %eax
	subl	-312(%rbp), %eax
	movl	%eax, %esi
	movl	-308(%rbp), %eax
	subq	$8, %rsp
	leaq	-292(%rbp), %rdx
	pushq	%rdx
	movl	$5126, %r9d
	movl	$6402, %r8d
	movl	$1, %ecx
	movl	$1, %edx
	movl	%eax, %edi
	call	glReadPixels@PLT
	addq	$16, %rsp
	.loc 1 92 0
	movss	-292(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm2
	movl	winH(%rip), %eax
	subl	-312(%rbp), %eax
	cvtsi2sd	%eax, %xmm1
	cvtsi2sd	-308(%rbp), %xmm0
	leaq	-288(%rbp), %rdx
	leaq	-144(%rbp), %rsi
	leaq	-272(%rbp), %rax
	leaq	objZ(%rip), %r9
	leaq	objY(%rip), %r8
	leaq	objX(%rip), %rcx
	movq	%rax, %rdi
	call	gluUnProject@PLT
	.loc 1 93 0
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L8
	call	__stack_chk_fail@PLT
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	getWorldCood, .-getWorldCood
	.globl	liner_search
	.type	liner_search, @function
liner_search:
.LFB8:
	.loc 1 96 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	%xmm0, -24(%rbp)
	movsd	%xmm1, -32(%rbp)
.LBB2:
	.loc 1 98 0
	movl	$0, -4(%rbp)
	jmp	.L10
.L14:
	.loc 1 99 0
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	subsd	-24(%rbp), %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, %ecx
	sarl	$31, %ecx
	xorl	%ecx, %eax
	movl	%eax, %edx
	subl	%ecx, %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rcx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	salq	$4, %rax
	movq	%rax, %rcx
	leaq	16+cats(%rip), %rax
	movsd	(%rcx,%rax), %xmm0
	subsd	-32(%rbp), %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, %ecx
	sarl	$31, %ecx
	xorl	%ecx, %eax
	subl	%ecx, %eax
	imull	%edx, %eax
	cvtsi2sd	%eax, %xmm0
	movsd	.LC8(%rip), %xmm1
	ucomisd	%xmm0, %xmm1
	jbe	.L16
	.loc 1 100 0
	movl	-4(%rbp), %eax
	jmp	.L13
.L16:
	.loc 1 98 0 discriminator 2
	addl	$1, -4(%rbp)
.L10:
	.loc 1 98 0 is_stmt 0 discriminator 1
	movl	n(%rip), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L14
.LBE2:
	.loc 1 102 0 is_stmt 1
	movl	$-1, %eax
.L13:
	.loc 1 103 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	liner_search, .-liner_search
	.globl	display
	.type	display, @function
display:
.LFB9:
	.loc 1 114 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	.loc 1 114 0
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 115 0
	movl	mode(%rip), %eax
	cmpl	$5, %eax
	jne	.L18
	.loc 1 116 0
	movl	$0, %eax
	call	shaking
	.loc 1 117 0
	movl	$0, %eax
	call	fusion_clearColor@PLT
	jmp	.L19
.L18:
	.loc 1 119 0
	pxor	%xmm3, %xmm3
	movss	.LC10(%rip), %xmm2
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	call	glClearColor@PLT
.L19:
	.loc 1 122 0
	movl	$16640, %edi
	call	glClear@PLT
	.loc 1 123 0
	movq	cam_angle(%rip), %rax
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	tan@PLT
	movapd	%xmm0, %xmm1
	movsd	.LC11(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	.LC12(%rip), %xmm1
	subsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	.LC12(%rip), %xmm4
	movsd	.LC8(%rip), %xmm3
	movsd	.LC13(%rip), %xmm2
	movsd	.LC14(%rip), %xmm8
	subq	$8, %rsp
	pxor	%xmm1, %xmm1
	leaq	-8(%rsp), %rsp
	movsd	%xmm1, (%rsp)
	movapd	%xmm4, %xmm7
	pxor	%xmm6, %xmm6
	movapd	%xmm3, %xmm5
	movapd	%xmm0, %xmm4
	pxor	%xmm3, %xmm3
	movapd	%xmm8, %xmm1
	pxor	%xmm0, %xmm0
	call	gluLookAt@PLT
	addq	$16, %rsp
	.loc 1 124 0
	movl	$5888, %edi
	call	glMatrixMode@PLT
	.loc 1 125 0
	call	glLoadIdentity@PLT
	.loc 1 128 0
	movl	$2896, %edi
	call	glDisable@PLT
	.loc 1 129 0
	call	glPushMatrix@PLT
	.loc 1 130 0
	movsd	.LC12(%rip), %xmm0
	movq	.LC15(%rip), %rax
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	glRotated@PLT
	.loc 1 132 0
	movsd	.LC16(%rip), %xmm1
	movsd	.LC17(%rip), %xmm0
	movq	.LC18(%rip), %rax
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	drawMap@PLT
	.loc 1 134 0
	movl	mode(%rip), %eax
	cmpl	$1, %eax
	je	.L20
	.loc 1 134 0 is_stmt 0 discriminator 1
	movl	mode(%rip), %eax
	cmpl	$2, %eax
	jne	.L21
.L20:
	.loc 1 135 0 is_stmt 1
	movsd	.LC18(%rip), %xmm0
	movapd	%xmm0, %xmm2
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	call	glTranslated@PLT
	.loc 1 136 0
	movsd	pointer_y(%rip), %xmm0
	movq	pointer_x(%rip), %rax
	movapd	%xmm0, %xmm1
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	drawPointer@PLT
	jmp	.L22
.L21:
	.loc 1 137 0
	movl	mode(%rip), %eax
	cmpl	$3, %eax
	jne	.L22
	.loc 1 138 0
	movsd	.LC18(%rip), %xmm0
	movapd	%xmm0, %xmm2
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	call	glTranslated@PLT
	.loc 1 139 0
	movl	rgb_pm(%rip), %ecx
	movl	rgb_flg(%rip), %edx
	movsd	pointer_y(%rip), %xmm0
	movq	pointer_x(%rip), %rax
	movl	%ecx, %esi
	movl	%edx, %edi
	movapd	%xmm0, %xmm1
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	drawColorPointer@PLT
.L22:
	.loc 1 142 0
	call	glPopMatrix@PLT
	.loc 1 144 0
	call	init3d@PLT
	.loc 1 145 0
	movl	mode(%rip), %eax
	cmpl	$4, %eax
	jne	.L23
	.loc 1 146 0
	movl	line_vec_num(%rip), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	.LC19(%rip), %xmm1
	divsd	%xmm1, %xmm0
	call	drawBucket@PLT
.L23:
	.loc 1 149 0
	leaq	camera(%rip), %rdi
	call	glMultMatrixf@PLT
	.loc 1 151 0
	movl	$60, %edi
	call	drawFloor@PLT
	.loc 1 152 0
	movl	mode(%rip), %eax
	cmpl	$5, %eax
	jne	.L24
	.loc 1 153 0
	movl	$0, %eax
	call	fusion_cloud@PLT
	jmp	.L25
.L24:
.LBB3:
	.loc 1 155 0
	movss	.LC10(%rip), %xmm0
	movss	%xmm0, -32(%rbp)
	movss	.LC10(%rip), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	.LC10(%rip), %xmm0
	movss	%xmm0, -24(%rbp)
	movss	.LC10(%rip), %xmm0
	movss	%xmm0, -20(%rbp)
	.loc 1 156 0
	leaq	-32(%rbp), %rax
	movq	%rax, %rdx
	movl	$5634, %esi
	movl	$1032, %edi
	call	glMaterialfv@PLT
.L25:
.LBE3:
	.loc 1 158 0
	call	drawCloud@PLT
	.loc 1 160 0
	movl	mode(%rip), %eax
	cmpl	$5, %eax
	je	.L26
	.loc 1 161 0
	call	updateFunc@PLT
.L26:
.LBB4:
	.loc 1 163 0
	movl	$0, -40(%rbp)
	jmp	.L27
.L28:
	.loc 1 164 0 discriminator 3
	movl	-40(%rbp), %eax
	movl	%eax, %edi
	call	drawCat@PLT
	.loc 1 163 0 discriminator 3
	addl	$1, -40(%rbp)
.L27:
	.loc 1 163 0 is_stmt 0 discriminator 1
	movl	n(%rip), %eax
	cmpl	%eax, -40(%rbp)
	jl	.L28
.LBE4:
	.loc 1 168 0 is_stmt 1
	call	glPushMatrix@PLT
	.loc 1 169 0
	movl	$2896, %edi
	call	glDisable@PLT
	.loc 1 170 0
	movsd	.LC12(%rip), %xmm1
	movsd	.LC12(%rip), %xmm0
	movq	.LC12(%rip), %rax
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	glColor3d@PLT
	.loc 1 171 0
	movss	.LC20(%rip), %xmm0
	call	glLineWidth@PLT
.LBB5:
	.loc 1 172 0
	movl	$0, -36(%rbp)
	jmp	.L29
.L30:
	.loc 1 173 0 discriminator 3
	movl	$1, %edi
	call	glBegin@PLT
	.loc 1 174 0 discriminator 3
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	16+line_vector(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	cvtsd2ss	%xmm0, %xmm2
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	8+line_vector(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	cvtsd2ss	%xmm0, %xmm1
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	line_vector(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	call	glVertex3f@PLT
	.loc 1 175 0 discriminator 3
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	16+line_vector(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	cvtsd2ss	%xmm0, %xmm2
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	8+line_vector(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	cvtsd2ss	%xmm0, %xmm1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	line_vector(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	call	glVertex3f@PLT
	.loc 1 176 0 discriminator 3
	call	glEnd@PLT
	.loc 1 172 0 discriminator 3
	addl	$1, -36(%rbp)
.L29:
	.loc 1 172 0 is_stmt 0 discriminator 1
	movl	line_vec_num(%rip), %eax
	subl	$1, %eax
	cmpl	%eax, -36(%rbp)
	jl	.L30
.LBE5:
	.loc 1 179 0 is_stmt 1
	movl	mode(%rip), %eax
	cmpl	$5, %eax
	jne	.L31
	.loc 1 180 0
	movl	$0, %eax
	call	fusion_update@PLT
	testl	%eax, %eax
	je	.L31
	.loc 1 181 0
	movl	$4, mode(%rip)
	.loc 1 182 0
	movl	$0, %eax
	call	line_init@PLT
	.loc 1 183 0
	movl	$0, line_flg(%rip)
.L31:
	.loc 1 187 0
	call	glPopMatrix@PLT
	.loc 1 190 0
	call	glutSwapBuffers@PLT
	.loc 1 191 0
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L32
	call	__stack_chk_fail@PLT
.L32:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	display, .-display
	.globl	reshape
	.type	reshape, @function
reshape:
.LFB10:
	.loc 1 202 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	.loc 1 203 0
	movl	-8(%rbp), %eax
	movl	%eax, winH(%rip)
	.loc 1 204 0
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %ecx
	movl	%eax, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	glViewport@PLT
	.loc 1 206 0
	movl	$5889, %edi
	call	glMatrixMode@PLT
	.loc 1 207 0
	call	glLoadIdentity@PLT
	.loc 1 208 0
	cvtsi2ss	-4(%rbp), %xmm0
	cvtsi2ss	-8(%rbp), %xmm1
	divss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	.LC21(%rip), %xmm2
	movsd	.LC22(%rip), %xmm1
	movq	.LC23(%rip), %rax
	movapd	%xmm2, %xmm3
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	call	gluPerspective@PLT
	.loc 1 209 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	reshape, .-reshape
	.section	.rodata
.LC24:
	.string	"1->%d\n"
	.text
	.globl	keyboard
	.type	keyboard, @function
keyboard:
.LFB11:
	.loc 1 216 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, %eax
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movb	%al, -20(%rbp)
	.loc 1 222 0
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC24(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 223 0
	movl	$0, -4(%rbp)
	.loc 1 370 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	keyboard, .-keyboard
	.globl	mouse
	.type	mouse, @function
mouse:
.LFB12:
	.loc 1 376 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$192, %rsp
	movl	%edi, -164(%rbp)
	movl	%esi, -168(%rbp)
	movl	%edx, -172(%rbp)
	movl	%ecx, -176(%rbp)
	.loc 1 376 0
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 377 0
	movl	$-1, -148(%rbp)
	.loc 1 379 0
	cmpl	$1, -168(%rbp)
	je	.L75
	.loc 1 382 0
	movl	-176(%rbp), %eax
	leal	30(%rax), %edx
	movl	-172(%rbp), %eax
	addl	$6, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	getWorldCood
	.loc 1 383 0
	movsd	objZ(%rip), %xmm0
	movq	objX(%rip), %rax
	movapd	%xmm0, %xmm1
	movq	%rax, -184(%rbp)
	movsd	-184(%rbp), %xmm0
	call	liner_search
	movl	%eax, -148(%rbp)
	.loc 1 386 0
	movl	mode(%rip), %eax
	cmpl	$2, %eax
	je	.L39
	cmpl	$3, %eax
	je	.L40
	cmpl	$1, %eax
	je	.L41
	.loc 1 452 0
	jmp	.L45
.L41:
	.loc 1 388 0
	cmpl	$0, -148(%rbp)
	js	.L76
	.loc 1 390 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	24+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	ucomisd	.LC25(%rip), %xmm0
	jp	.L43
	ucomisd	.LC25(%rip), %xmm0
	jne	.L43
	.loc 1 391 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	24+cats(%rip), %rax
	movsd	.LC26(%rip), %xmm0
	movsd	%xmm0, (%rdx,%rax)
	.loc 1 392 0
	jmp	.L45
.L43:
	.loc 1 393 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	24+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	ucomisd	.LC26(%rip), %xmm0
	jp	.L46
	ucomisd	.LC26(%rip), %xmm0
	jne	.L46
	.loc 1 394 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	24+cats(%rip), %rax
	movsd	.LC12(%rip), %xmm0
	movsd	%xmm0, (%rdx,%rax)
	.loc 1 395 0
	jmp	.L45
.L46:
	.loc 1 398 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	60+cats(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	$1, %eax
	je	.L76
	.loc 1 399 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	60+cats(%rip), %rax
	movl	$1, (%rdx,%rax)
	.loc 1 400 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	64+cats(%rip), %rax
	movl	$0, (%rdx,%rax)
	.loc 1 403 0
	jmp	.L76
.L39:
	.loc 1 406 0
	movl	pick_obj(%rip), %eax
	testl	%eax, %eax
	js	.L48
	.loc 1 407 0
	movl	pick_obj(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	124+cats(%rip), %rax
	pxor	%xmm0, %xmm0
	movss	%xmm0, (%rdx,%rax)
	.loc 1 408 0
	movl	pick_obj(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	60+cats(%rip), %rax
	movl	$2, (%rdx,%rax)
	.loc 1 409 0
	movl	$-1, pick_obj(%rip)
	.loc 1 421 0
	jmp	.L77
.L48:
	.loc 1 411 0
	cmpl	$0, -148(%rbp)
	js	.L77
.LBB6:
	.loc 1 412 0
	movl	-148(%rbp), %eax
	movl	%eax, pick_obj(%rip)
	.loc 1 413 0
	movl	pick_obj(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	60+cats(%rip), %rax
	movl	$6, (%rdx,%rax)
	.loc 1 416 0
	leaq	-144(%rbp), %rax
	leaq	inv(%rip), %rsi
	movq	%rax, %rdi
	call	copyMat@PLT
	.loc 1 417 0
	leaq	-80(%rbp), %rax
	movsd	.LC27(%rip), %xmm1
	movsd	.LC28(%rip), %xmm0
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	movq	%rax, %rdi
	call	tlMat@PLT
	leaq	-80(%rbp), %rdx
	leaq	-144(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	dotMat@PLT
	.loc 1 418 0
	movl	pick_obj(%rip), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	leaq	64(%rax), %rdx
	leaq	cats(%rip), %rax
	addq	%rdx, %rax
	leaq	8(%rax), %rdx
	leaq	-144(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	copyMat@PLT
.LBE6:
	.loc 1 421 0
	jmp	.L77
.L40:
	.loc 1 424 0
	cmpl	$0, -148(%rbp)
	js	.L78
	.loc 1 425 0
	movl	rgb_flg(%rip), %eax
	cmpl	$1, %eax
	je	.L51
	cmpl	$2, %eax
	je	.L52
	testl	%eax, %eax
	je	.L53
	.loc 1 449 0
	jmp	.L78
.L53:
	.loc 1 427 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	32+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm1
	movl	rgb_pm(%rip), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	.LC29(%rip), %xmm2
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	32+cats(%rip), %rax
	movsd	%xmm0, (%rdx,%rax)
	.loc 1 428 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	32+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	movsd	.LC12(%rip), %xmm1
	ucomisd	%xmm1, %xmm0
	jbe	.L54
	.loc 1 429 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	32+cats(%rip), %rax
	movsd	.LC12(%rip), %xmm0
	movsd	%xmm0, (%rdx,%rax)
.L54:
	.loc 1 430 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	32+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm1
	pxor	%xmm0, %xmm0
	ucomisd	%xmm1, %xmm0
	ja	.L70
	.loc 1 432 0
	jmp	.L50
.L70:
	.loc 1 431 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	32+cats(%rip), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, (%rdx,%rax)
	.loc 1 432 0
	jmp	.L50
.L51:
	.loc 1 434 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	40+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm1
	movl	rgb_pm(%rip), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	.LC29(%rip), %xmm2
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	40+cats(%rip), %rax
	movsd	%xmm0, (%rdx,%rax)
	.loc 1 435 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	40+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	movsd	.LC12(%rip), %xmm1
	ucomisd	%xmm1, %xmm0
	jbe	.L58
	.loc 1 436 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	40+cats(%rip), %rax
	movsd	.LC12(%rip), %xmm0
	movsd	%xmm0, (%rdx,%rax)
.L58:
	.loc 1 437 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	40+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm1
	pxor	%xmm0, %xmm0
	ucomisd	%xmm1, %xmm0
	ja	.L72
	.loc 1 439 0
	jmp	.L50
.L72:
	.loc 1 438 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	40+cats(%rip), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, (%rdx,%rax)
	.loc 1 439 0
	jmp	.L50
.L52:
	.loc 1 441 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	48+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm1
	movl	rgb_pm(%rip), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	.LC29(%rip), %xmm2
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	48+cats(%rip), %rax
	movsd	%xmm0, (%rdx,%rax)
	.loc 1 442 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	48+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	movsd	.LC12(%rip), %xmm1
	ucomisd	%xmm1, %xmm0
	jbe	.L62
	.loc 1 443 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	48+cats(%rip), %rax
	movsd	.LC12(%rip), %xmm0
	movsd	%xmm0, (%rdx,%rax)
.L62:
	.loc 1 444 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	48+cats(%rip), %rax
	movsd	(%rdx,%rax), %xmm1
	pxor	%xmm0, %xmm0
	ucomisd	%xmm1, %xmm0
	ja	.L74
	.loc 1 446 0
	jmp	.L79
.L74:
	.loc 1 445 0
	movl	-148(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	leaq	48+cats(%rip), %rax
	pxor	%xmm0, %xmm0
	movsd	%xmm0, (%rdx,%rax)
.L79:
	.loc 1 446 0
	nop
.L50:
	.loc 1 449 0 discriminator 3
	jmp	.L78
.L76:
	.loc 1 403 0
	nop
	jmp	.L45
.L77:
	.loc 1 421 0
	nop
	jmp	.L45
.L78:
	.loc 1 449 0
	nop
.L45:
	.loc 1 455 0
	call	glutPostRedisplay@PLT
	jmp	.L35
.L75:
	.loc 1 380 0
	nop
.L35:
	.loc 1 456 0
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L66
	call	__stack_chk_fail@PLT
.L66:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	mouse, .-mouse
	.globl	motion
	.type	motion, @function
motion:
.LFB13:
	.loc 1 461 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	.loc 1 463 0
	movl	$600, %eax
	subl	-4(%rbp), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, pointer_x(%rip)
	.loc 1 464 0
	movl	$730, %eax
	subl	-8(%rbp), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	.LC30(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, pointer_y(%rip)
	.loc 1 466 0
	call	glutPostRedisplay@PLT
	.loc 1 467 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	motion, .-motion
	.globl	idle
	.type	idle, @function
idle:
.LFB14:
	.loc 1 473 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	.loc 1 474 0
	call	glutPostRedisplay@PLT
	.loc 1 475 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	idle, .-idle
	.globl	main
	.type	main, @function
main:
.LFB15:
	.loc 1 481 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	.loc 1 483 0
	movq	-16(%rbp), %rdx
	leaq	-4(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	glutInit@PLT
	.loc 1 484 0
	movl	$18, %edi
	call	glutInitDisplayMode@PLT
	.loc 1 485 0
	movl	winH(%rip), %edx
	movl	winW(%rip), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	glutInitWindowSize@PLT
	.loc 1 486 0
	movl	$50, %esi
	movl	$50, %edi
	call	glutInitWindowPosition@PLT
	.loc 1 487 0
	movl	mode(%rip), %eax
	movl	%eax, %eax
	leaq	0(,%rax,8), %rdx
	leaq	mode_name(%rip), %rax
	movq	(%rdx,%rax), %rax
	movq	%rax, %rdi
	call	glutCreateWindow@PLT
	.loc 1 489 0
	call	init
	.loc 1 491 0
	leaq	display(%rip), %rdi
	call	glutDisplayFunc@PLT
	.loc 1 492 0
	leaq	reshape(%rip), %rdi
	call	glutReshapeFunc@PLT
	.loc 1 493 0
	leaq	keyboard(%rip), %rdi
	call	glutKeyboardFunc@PLT
	.loc 1 494 0
	leaq	idle(%rip), %rdi
	call	glutIdleFunc@PLT
	.loc 1 496 0
	leaq	mouse(%rip), %rdi
	call	glutMouseFunc@PLT
	.loc 1 498 0
	movl	$101, %edi
	call	glutSetCursor@PLT
	.loc 1 499 0
	leaq	motion(%rip), %rdi
	call	glutPassiveMotionFunc@PLT
	.loc 1 501 0
	call	glutMainLoop@PLT
	.loc 1 503 0
	movl	$0, %eax
	.loc 1 504 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	main, .-main
	.local	count.18428
	.comm	count.18428,4,4
	.section	.rodata
	.align 8
.LC5:
	.long	515396076
	.long	1068624773
	.align 16
.LC6:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.align 8
.LC8:
	.long	0
	.long	1073741824
	.align 4
.LC10:
	.long	1065353216
	.align 8
.LC11:
	.long	0
	.long	1082310656
	.align 8
.LC12:
	.long	0
	.long	1072693248
	.align 8
.LC13:
	.long	0
	.long	-1071382528
	.align 8
.LC14:
	.long	0
	.long	1075052544
	.align 8
.LC15:
	.long	3461997116
	.long	1077047128
	.align 8
.LC16:
	.long	0
	.long	1078853632
	.align 8
.LC17:
	.long	3435973837
	.long	1075104972
	.align 8
.LC18:
	.long	0
	.long	-1072431104
	.align 8
.LC19:
	.long	0
	.long	1077805056
	.align 4
.LC20:
	.long	1084227584
	.align 8
.LC21:
	.long	0
	.long	1080623104
	.align 8
.LC22:
	.long	0
	.long	1075314688
	.align 8
.LC23:
	.long	0
	.long	1078362112
	.align 8
.LC25:
	.long	858993459
	.long	1071854387
	.align 8
.LC26:
	.long	2576980378
	.long	1072273817
	.align 8
.LC27:
	.long	0
	.long	1077149696
	.align 8
.LC28:
	.long	0
	.long	1074790400
	.align 8
.LC29:
	.long	2576980378
	.long	1070176665
	.align 8
.LC30:
	.long	0
	.long	1080549376
	.text
.Letext0:
	.file 2 "/usr/include/GL/gl.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/GL/glu.h"
	.file 5 "/usr/include/GL/freeglut_std.h"
	.file 6 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 7 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 8 "/usr/include/stdio.h"
	.file 9 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 10 "/usr/include/unistd.h"
	.file 11 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
	.file 12 "/usr/include/math.h"
	.file 13 "/usr/include/time.h"
	.file 14 "draw_function.h"
	.file 15 "matrix_function.h"
	.file 16 "line.h"
	.file 17 "action.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xb28
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF146
	.byte	0xc
	.long	.LASF147
	.long	.LASF148
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF3
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF4
	.uleb128 0x4
	.long	.LASF5
	.byte	0x2
	.byte	0x7e
	.long	0x49
	.uleb128 0x4
	.long	.LASF6
	.byte	0x2
	.byte	0x7f
	.long	0x6d
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.long	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.long	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF10
	.uleb128 0x4
	.long	.LASF11
	.byte	0x3
	.byte	0x8c
	.long	0x82
	.uleb128 0x4
	.long	.LASF12
	.byte	0x3
	.byte	0x8d
	.long	0x82
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0xa7
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF13
	.uleb128 0x7
	.long	0xa7
	.uleb128 0x8
	.long	.LASF14
	.byte	0x4
	.value	0x113
	.long	0xbf
	.uleb128 0x9
	.long	.LASF14
	.uleb128 0x8
	.long	.LASF15
	.byte	0x4
	.value	0x118
	.long	0xb3
	.uleb128 0xa
	.long	.LASF16
	.byte	0x5
	.byte	0xd7
	.long	0x9f
	.uleb128 0xa
	.long	.LASF17
	.byte	0x5
	.byte	0xd8
	.long	0x9f
	.uleb128 0xa
	.long	.LASF18
	.byte	0x5
	.byte	0xd9
	.long	0x9f
	.uleb128 0xa
	.long	.LASF19
	.byte	0x5
	.byte	0xda
	.long	0x9f
	.uleb128 0xa
	.long	.LASF20
	.byte	0x5
	.byte	0xdb
	.long	0x9f
	.uleb128 0xa
	.long	.LASF21
	.byte	0x5
	.byte	0xdc
	.long	0x9f
	.uleb128 0xa
	.long	.LASF22
	.byte	0x5
	.byte	0xdd
	.long	0x9f
	.uleb128 0xa
	.long	.LASF23
	.byte	0x5
	.byte	0xde
	.long	0x9f
	.uleb128 0xa
	.long	.LASF24
	.byte	0x5
	.byte	0xdf
	.long	0x9f
	.uleb128 0x4
	.long	.LASF25
	.byte	0x6
	.byte	0xd8
	.long	0x7b
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF26
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF27
	.uleb128 0xb
	.long	.LASF57
	.byte	0xd8
	.byte	0x7
	.byte	0xf5
	.long	0x2cc
	.uleb128 0xc
	.long	.LASF28
	.byte	0x7
	.byte	0xf6
	.long	0x49
	.byte	0
	.uleb128 0xc
	.long	.LASF29
	.byte	0x7
	.byte	0xfb
	.long	0xa1
	.byte	0x8
	.uleb128 0xc
	.long	.LASF30
	.byte	0x7
	.byte	0xfc
	.long	0xa1
	.byte	0x10
	.uleb128 0xc
	.long	.LASF31
	.byte	0x7
	.byte	0xfd
	.long	0xa1
	.byte	0x18
	.uleb128 0xc
	.long	.LASF32
	.byte	0x7
	.byte	0xfe
	.long	0xa1
	.byte	0x20
	.uleb128 0xc
	.long	.LASF33
	.byte	0x7
	.byte	0xff
	.long	0xa1
	.byte	0x28
	.uleb128 0xd
	.long	.LASF34
	.byte	0x7
	.value	0x100
	.long	0xa1
	.byte	0x30
	.uleb128 0xd
	.long	.LASF35
	.byte	0x7
	.value	0x101
	.long	0xa1
	.byte	0x38
	.uleb128 0xd
	.long	.LASF36
	.byte	0x7
	.value	0x102
	.long	0xa1
	.byte	0x40
	.uleb128 0xd
	.long	.LASF37
	.byte	0x7
	.value	0x104
	.long	0xa1
	.byte	0x48
	.uleb128 0xd
	.long	.LASF38
	.byte	0x7
	.value	0x105
	.long	0xa1
	.byte	0x50
	.uleb128 0xd
	.long	.LASF39
	.byte	0x7
	.value	0x106
	.long	0xa1
	.byte	0x58
	.uleb128 0xd
	.long	.LASF40
	.byte	0x7
	.value	0x108
	.long	0x304
	.byte	0x60
	.uleb128 0xd
	.long	.LASF41
	.byte	0x7
	.value	0x10a
	.long	0x30a
	.byte	0x68
	.uleb128 0xd
	.long	.LASF42
	.byte	0x7
	.value	0x10c
	.long	0x49
	.byte	0x70
	.uleb128 0xd
	.long	.LASF43
	.byte	0x7
	.value	0x110
	.long	0x49
	.byte	0x74
	.uleb128 0xd
	.long	.LASF44
	.byte	0x7
	.value	0x112
	.long	0x89
	.byte	0x78
	.uleb128 0xd
	.long	.LASF45
	.byte	0x7
	.value	0x116
	.long	0x50
	.byte	0x80
	.uleb128 0xd
	.long	.LASF46
	.byte	0x7
	.value	0x117
	.long	0x3b
	.byte	0x82
	.uleb128 0xd
	.long	.LASF47
	.byte	0x7
	.value	0x118
	.long	0x310
	.byte	0x83
	.uleb128 0xd
	.long	.LASF48
	.byte	0x7
	.value	0x11c
	.long	0x320
	.byte	0x88
	.uleb128 0xd
	.long	.LASF49
	.byte	0x7
	.value	0x125
	.long	0x94
	.byte	0x90
	.uleb128 0xd
	.long	.LASF50
	.byte	0x7
	.value	0x12d
	.long	0x9f
	.byte	0x98
	.uleb128 0xd
	.long	.LASF51
	.byte	0x7
	.value	0x12e
	.long	0x9f
	.byte	0xa0
	.uleb128 0xd
	.long	.LASF52
	.byte	0x7
	.value	0x12f
	.long	0x9f
	.byte	0xa8
	.uleb128 0xd
	.long	.LASF53
	.byte	0x7
	.value	0x130
	.long	0x9f
	.byte	0xb0
	.uleb128 0xd
	.long	.LASF54
	.byte	0x7
	.value	0x132
	.long	0x133
	.byte	0xb8
	.uleb128 0xd
	.long	.LASF55
	.byte	0x7
	.value	0x133
	.long	0x49
	.byte	0xc0
	.uleb128 0xd
	.long	.LASF56
	.byte	0x7
	.value	0x135
	.long	0x326
	.byte	0xc4
	.byte	0
	.uleb128 0xe
	.long	.LASF149
	.byte	0x7
	.byte	0x9a
	.uleb128 0xb
	.long	.LASF58
	.byte	0x18
	.byte	0x7
	.byte	0xa0
	.long	0x304
	.uleb128 0xc
	.long	.LASF59
	.byte	0x7
	.byte	0xa1
	.long	0x304
	.byte	0
	.uleb128 0xc
	.long	.LASF60
	.byte	0x7
	.byte	0xa2
	.long	0x30a
	.byte	0x8
	.uleb128 0xc
	.long	.LASF61
	.byte	0x7
	.byte	0xa6
	.long	0x49
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x2d3
	.uleb128 0x6
	.byte	0x8
	.long	0x14c
	.uleb128 0xf
	.long	0xa7
	.long	0x320
	.uleb128 0x10
	.long	0x7b
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x2cc
	.uleb128 0xf
	.long	0xa7
	.long	0x336
	.uleb128 0x10
	.long	0x7b
	.byte	0x13
	.byte	0
	.uleb128 0x9
	.long	.LASF62
	.uleb128 0x11
	.long	.LASF63
	.byte	0x7
	.value	0x13f
	.long	0x336
	.uleb128 0x11
	.long	.LASF64
	.byte	0x7
	.value	0x140
	.long	0x336
	.uleb128 0x11
	.long	.LASF65
	.byte	0x7
	.value	0x141
	.long	0x336
	.uleb128 0x6
	.byte	0x8
	.long	0xae
	.uleb128 0x7
	.long	0x35f
	.uleb128 0xa
	.long	.LASF66
	.byte	0x8
	.byte	0x87
	.long	0x30a
	.uleb128 0xa
	.long	.LASF67
	.byte	0x8
	.byte	0x88
	.long	0x30a
	.uleb128 0xa
	.long	.LASF68
	.byte	0x8
	.byte	0x89
	.long	0x30a
	.uleb128 0xa
	.long	.LASF69
	.byte	0x9
	.byte	0x1a
	.long	0x49
	.uleb128 0xf
	.long	0x365
	.long	0x3a1
	.uleb128 0x12
	.byte	0
	.uleb128 0x7
	.long	0x396
	.uleb128 0xa
	.long	.LASF70
	.byte	0x9
	.byte	0x1b
	.long	0x3a1
	.uleb128 0x11
	.long	.LASF71
	.byte	0xa
	.value	0x222
	.long	0x3bd
	.uleb128 0x6
	.byte	0x8
	.long	0xa1
	.uleb128 0xa
	.long	.LASF72
	.byte	0xb
	.byte	0x24
	.long	0xa1
	.uleb128 0xa
	.long	.LASF73
	.byte	0xb
	.byte	0x32
	.long	0x49
	.uleb128 0xa
	.long	.LASF74
	.byte	0xb
	.byte	0x37
	.long	0x49
	.uleb128 0xa
	.long	.LASF75
	.byte	0xb
	.byte	0x3b
	.long	0x49
	.uleb128 0x11
	.long	.LASF76
	.byte	0xc
	.value	0x1e9
	.long	0x49
	.uleb128 0xf
	.long	0xa1
	.long	0x40b
	.uleb128 0x10
	.long	0x7b
	.byte	0x1
	.byte	0
	.uleb128 0xa
	.long	.LASF77
	.byte	0xd
	.byte	0x9f
	.long	0x3fb
	.uleb128 0xa
	.long	.LASF78
	.byte	0xd
	.byte	0xa0
	.long	0x49
	.uleb128 0xa
	.long	.LASF79
	.byte	0xd
	.byte	0xa1
	.long	0x82
	.uleb128 0xa
	.long	.LASF80
	.byte	0xd
	.byte	0xa6
	.long	0x3fb
	.uleb128 0xa
	.long	.LASF81
	.byte	0xd
	.byte	0xae
	.long	0x49
	.uleb128 0xa
	.long	.LASF82
	.byte	0xd
	.byte	0xaf
	.long	0x82
	.uleb128 0xa
	.long	.LASF83
	.byte	0xe
	.byte	0x8
	.long	0x458
	.uleb128 0x6
	.byte	0x8
	.long	0xc4
	.uleb128 0xa
	.long	.LASF84
	.byte	0xe
	.byte	0x8
	.long	0x458
	.uleb128 0x13
	.byte	0x90
	.byte	0xf
	.byte	0x8
	.long	0x50e
	.uleb128 0x14
	.string	"x"
	.byte	0xf
	.byte	0x9
	.long	0x74
	.byte	0
	.uleb128 0x14
	.string	"y"
	.byte	0xf
	.byte	0x9
	.long	0x74
	.byte	0x8
	.uleb128 0x14
	.string	"z"
	.byte	0xf
	.byte	0x9
	.long	0x74
	.byte	0x10
	.uleb128 0xc
	.long	.LASF85
	.byte	0xf
	.byte	0x9
	.long	0x74
	.byte	0x18
	.uleb128 0x14
	.string	"r"
	.byte	0xf
	.byte	0x9
	.long	0x74
	.byte	0x20
	.uleb128 0x14
	.string	"g"
	.byte	0xf
	.byte	0x9
	.long	0x74
	.byte	0x28
	.uleb128 0x14
	.string	"b"
	.byte	0xf
	.byte	0x9
	.long	0x74
	.byte	0x30
	.uleb128 0xc
	.long	.LASF86
	.byte	0xf
	.byte	0xa
	.long	0x49
	.byte	0x38
	.uleb128 0xc
	.long	.LASF87
	.byte	0xf
	.byte	0xa
	.long	0x49
	.byte	0x3c
	.uleb128 0xc
	.long	.LASF88
	.byte	0xf
	.byte	0xa
	.long	0x49
	.byte	0x40
	.uleb128 0xc
	.long	.LASF89
	.byte	0xf
	.byte	0xa
	.long	0x49
	.byte	0x44
	.uleb128 0xc
	.long	.LASF90
	.byte	0xf
	.byte	0xb
	.long	0x50e
	.byte	0x48
	.uleb128 0xc
	.long	.LASF91
	.byte	0xf
	.byte	0xc
	.long	0x6d
	.byte	0x88
	.uleb128 0x14
	.string	"flg"
	.byte	0xf
	.byte	0xd
	.long	0x49
	.byte	0x8c
	.byte	0
	.uleb128 0xf
	.long	0x62
	.long	0x51e
	.uleb128 0x10
	.long	0x7b
	.byte	0xf
	.byte	0
	.uleb128 0x15
	.string	"Cat"
	.byte	0xf
	.byte	0xe
	.long	0x469
	.uleb128 0x13
	.byte	0x40
	.byte	0xf
	.byte	0xf
	.long	0x53e
	.uleb128 0xc
	.long	.LASF90
	.byte	0xf
	.byte	0xf
	.long	0x50e
	.byte	0
	.byte	0
	.uleb128 0x4
	.long	.LASF92
	.byte	0xf
	.byte	0xf
	.long	0x529
	.uleb128 0x16
	.string	"n"
	.byte	0xf
	.byte	0x11
	.long	0x49
	.uleb128 0xf
	.long	0x51e
	.long	0x55d
	.uleb128 0x12
	.byte	0
	.uleb128 0xa
	.long	.LASF93
	.byte	0xf
	.byte	0x12
	.long	0x552
	.uleb128 0xf
	.long	0x62
	.long	0x573
	.uleb128 0x12
	.byte	0
	.uleb128 0xa
	.long	.LASF94
	.byte	0xf
	.byte	0x13
	.long	0x568
	.uleb128 0x16
	.string	"inv"
	.byte	0xf
	.byte	0x14
	.long	0x568
	.uleb128 0x17
	.byte	0x7
	.byte	0x4
	.long	0x2d
	.byte	0x11
	.byte	0x9
	.long	0x5c1
	.uleb128 0x18
	.long	.LASF95
	.byte	0
	.uleb128 0x18
	.long	.LASF96
	.byte	0x1
	.uleb128 0x18
	.long	.LASF97
	.byte	0x2
	.uleb128 0x18
	.long	.LASF98
	.byte	0x3
	.uleb128 0x18
	.long	.LASF99
	.byte	0x4
	.uleb128 0x19
	.string	"DIE"
	.byte	0x5
	.uleb128 0x18
	.long	.LASF100
	.byte	0x6
	.byte	0
	.uleb128 0x13
	.byte	0x18
	.byte	0x10
	.byte	0x4
	.long	0x5e8
	.uleb128 0x14
	.string	"x"
	.byte	0x10
	.byte	0x5
	.long	0x74
	.byte	0
	.uleb128 0x14
	.string	"y"
	.byte	0x10
	.byte	0x5
	.long	0x74
	.byte	0x8
	.uleb128 0x14
	.string	"z"
	.byte	0x10
	.byte	0x5
	.long	0x74
	.byte	0x10
	.byte	0
	.uleb128 0x4
	.long	.LASF101
	.byte	0x10
	.byte	0x6
	.long	0x5c1
	.uleb128 0xf
	.long	0x5e8
	.long	0x5fe
	.uleb128 0x12
	.byte	0
	.uleb128 0xa
	.long	.LASF102
	.byte	0x10
	.byte	0x7
	.long	0x5f3
	.uleb128 0xa
	.long	.LASF103
	.byte	0x10
	.byte	0x8
	.long	0x49
	.uleb128 0x1a
	.long	.LASF104
	.byte	0x1
	.byte	0x15
	.long	0x49
	.uleb128 0x9
	.byte	0x3
	.quad	winW
	.uleb128 0x1a
	.long	.LASF105
	.byte	0x1
	.byte	0x15
	.long	0x49
	.uleb128 0x9
	.byte	0x3
	.quad	winH
	.uleb128 0x1a
	.long	.LASF106
	.byte	0x1
	.byte	0x17
	.long	0x74
	.uleb128 0x9
	.byte	0x3
	.quad	pointer_x
	.uleb128 0x1a
	.long	.LASF107
	.byte	0x1
	.byte	0x17
	.long	0x74
	.uleb128 0x9
	.byte	0x3
	.quad	pointer_y
	.uleb128 0x1a
	.long	.LASF108
	.byte	0x1
	.byte	0x19
	.long	0x74
	.uleb128 0x9
	.byte	0x3
	.quad	objX
	.uleb128 0x1a
	.long	.LASF109
	.byte	0x1
	.byte	0x19
	.long	0x74
	.uleb128 0x9
	.byte	0x3
	.quad	objY
	.uleb128 0x1a
	.long	.LASF110
	.byte	0x1
	.byte	0x19
	.long	0x74
	.uleb128 0x9
	.byte	0x3
	.quad	objZ
	.uleb128 0x1a
	.long	.LASF111
	.byte	0x1
	.byte	0x1b
	.long	0x74
	.uleb128 0x9
	.byte	0x3
	.quad	cam_height
	.uleb128 0x1a
	.long	.LASF112
	.byte	0x1
	.byte	0x1c
	.long	0x74
	.uleb128 0x9
	.byte	0x3
	.quad	cam_angle
	.uleb128 0x17
	.byte	0x7
	.byte	0x4
	.long	0x2d
	.byte	0x1
	.byte	0x1e
	.long	0x703
	.uleb128 0x18
	.long	.LASF113
	.byte	0
	.uleb128 0x18
	.long	.LASF114
	.byte	0x1
	.uleb128 0x18
	.long	.LASF115
	.byte	0x2
	.uleb128 0x18
	.long	.LASF116
	.byte	0x3
	.uleb128 0x18
	.long	.LASF117
	.byte	0x4
	.uleb128 0x18
	.long	.LASF118
	.byte	0x5
	.byte	0
	.uleb128 0x4
	.long	.LASF119
	.byte	0x1
	.byte	0x25
	.long	0x6d1
	.uleb128 0xf
	.long	0x35f
	.long	0x71e
	.uleb128 0x10
	.long	0x7b
	.byte	0x4
	.byte	0
	.uleb128 0x1a
	.long	.LASF120
	.byte	0x1
	.byte	0x26
	.long	0x70e
	.uleb128 0x9
	.byte	0x3
	.quad	mode_name
	.uleb128 0x1a
	.long	.LASF121
	.byte	0x1
	.byte	0x27
	.long	0x703
	.uleb128 0x9
	.byte	0x3
	.quad	mode
	.uleb128 0x1a
	.long	.LASF122
	.byte	0x1
	.byte	0x29
	.long	0x49
	.uleb128 0x9
	.byte	0x3
	.quad	rgb_flg
	.uleb128 0x1a
	.long	.LASF123
	.byte	0x1
	.byte	0x2a
	.long	0x49
	.uleb128 0x9
	.byte	0x3
	.quad	rgb_pm
	.uleb128 0xa
	.long	.LASF124
	.byte	0x1
	.byte	0x2c
	.long	0x49
	.uleb128 0x1a
	.long	.LASF125
	.byte	0x1
	.byte	0x2e
	.long	0x49
	.uleb128 0x9
	.byte	0x3
	.quad	line_flg
	.uleb128 0x1b
	.long	.LASF136
	.byte	0x1
	.value	0x1e0
	.long	0x49
	.quad	.LFB15
	.quad	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x7d3
	.uleb128 0x1c
	.long	.LASF126
	.byte	0x1
	.value	0x1e0
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1c
	.long	.LASF127
	.byte	0x1
	.value	0x1e0
	.long	0x3bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x1d
	.long	.LASF150
	.byte	0x1
	.value	0x1d8
	.quad	.LFB14
	.quad	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1e
	.long	.LASF128
	.byte	0x1
	.value	0x1cd
	.quad	.LFB13
	.quad	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x826
	.uleb128 0x1f
	.string	"x"
	.byte	0x1
	.value	0x1cd
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1f
	.string	"y"
	.byte	0x1
	.value	0x1cd
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1e
	.long	.LASF129
	.byte	0x1
	.value	0x177
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0x8af
	.uleb128 0x1c
	.long	.LASF130
	.byte	0x1
	.value	0x177
	.long	0x49
	.uleb128 0x3
	.byte	0x91
	.sleb128 -180
	.uleb128 0x1c
	.long	.LASF131
	.byte	0x1
	.value	0x177
	.long	0x49
	.uleb128 0x3
	.byte	0x91
	.sleb128 -184
	.uleb128 0x1f
	.string	"x"
	.byte	0x1
	.value	0x177
	.long	0x49
	.uleb128 0x3
	.byte	0x91
	.sleb128 -188
	.uleb128 0x1f
	.string	"y"
	.byte	0x1
	.value	0x177
	.long	0x49
	.uleb128 0x3
	.byte	0x91
	.sleb128 -192
	.uleb128 0x20
	.string	"i"
	.byte	0x1
	.value	0x179
	.long	0x49
	.uleb128 0x3
	.byte	0x91
	.sleb128 -164
	.uleb128 0x21
	.quad	.LBB6
	.quad	.LBE6-.LBB6
	.uleb128 0x20
	.string	"t"
	.byte	0x1
	.value	0x19f
	.long	0x50e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -160
	.byte	0
	.byte	0
	.uleb128 0x22
	.long	.LASF132
	.byte	0x1
	.byte	0xd7
	.quad	.LFB11
	.quad	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.long	0x90d
	.uleb128 0x23
	.string	"key"
	.byte	0x1
	.byte	0xd7
	.long	0x34
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x23
	.string	"x"
	.byte	0x1
	.byte	0xd7
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x23
	.string	"y"
	.byte	0x1
	.byte	0xd7
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x24
	.string	"rdx"
	.byte	0x1
	.byte	0xdd
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x24
	.string	"i"
	.byte	0x1
	.byte	0xdf
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x22
	.long	.LASF133
	.byte	0x1
	.byte	0xc9
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0x943
	.uleb128 0x23
	.string	"w"
	.byte	0x1
	.byte	0xc9
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x23
	.string	"h"
	.byte	0x1
	.byte	0xc9
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x22
	.long	.LASF134
	.byte	0x1
	.byte	0x71
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0x9c5
	.uleb128 0x25
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.long	0x984
	.uleb128 0x26
	.long	.LASF135
	.byte	0x1
	.byte	0x9b
	.long	0x9c5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x25
	.quad	.LBB4
	.quad	.LBE4-.LBB4
	.long	0x9a6
	.uleb128 0x24
	.string	"i"
	.byte	0x1
	.byte	0xa3
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.uleb128 0x21
	.quad	.LBB5
	.quad	.LBE5-.LBB5
	.uleb128 0x24
	.string	"k"
	.byte	0x1
	.byte	0xac
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0
	.byte	0
	.uleb128 0xf
	.long	0x62
	.long	0x9d5
	.uleb128 0x10
	.long	0x7b
	.byte	0x3
	.byte	0
	.uleb128 0x27
	.long	.LASF137
	.byte	0x1
	.byte	0x60
	.long	0x49
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0xa2d
	.uleb128 0x23
	.string	"x"
	.byte	0x1
	.byte	0x60
	.long	0x74
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x23
	.string	"z"
	.byte	0x1
	.byte	0x60
	.long	0x74
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x21
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x24
	.string	"i"
	.byte	0x1
	.byte	0x62
	.long	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x22
	.long	.LASF138
	.byte	0x1
	.byte	0x4e
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0xaa3
	.uleb128 0x28
	.long	.LASF139
	.byte	0x1
	.byte	0x4e
	.long	0x49
	.uleb128 0x3
	.byte	0x91
	.sleb128 -324
	.uleb128 0x28
	.long	.LASF140
	.byte	0x1
	.byte	0x4e
	.long	0x49
	.uleb128 0x3
	.byte	0x91
	.sleb128 -328
	.uleb128 0x26
	.long	.LASF141
	.byte	0x1
	.byte	0x50
	.long	0xaa3
	.uleb128 0x3
	.byte	0x91
	.sleb128 -288
	.uleb128 0x26
	.long	.LASF142
	.byte	0x1
	.byte	0x53
	.long	0xaa3
	.uleb128 0x3
	.byte	0x91
	.sleb128 -160
	.uleb128 0x26
	.long	.LASF143
	.byte	0x1
	.byte	0x56
	.long	0xab3
	.uleb128 0x3
	.byte	0x91
	.sleb128 -304
	.uleb128 0x24
	.string	"z"
	.byte	0x1
	.byte	0x59
	.long	0x6d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -308
	.byte	0
	.uleb128 0xf
	.long	0x74
	.long	0xab3
	.uleb128 0x10
	.long	0x7b
	.byte	0xf
	.byte	0
	.uleb128 0xf
	.long	0x49
	.long	0xac3
	.uleb128 0x10
	.long	0x7b
	.byte	0x3
	.byte	0
	.uleb128 0x29
	.long	.LASF151
	.byte	0x1
	.byte	0x3f
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0xb12
	.uleb128 0x26
	.long	.LASF144
	.byte	0x1
	.byte	0x40
	.long	0x49
	.uleb128 0x9
	.byte	0x3
	.quad	count.18428
	.uleb128 0x26
	.long	.LASF145
	.byte	0x1
	.byte	0x41
	.long	0x53e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x24
	.string	"y"
	.byte	0x1
	.byte	0x42
	.long	0x74
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.byte	0
	.uleb128 0x2a
	.long	.LASF152
	.byte	0x1
	.byte	0x34
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF98:
	.string	"SLEEP"
.LASF85:
	.string	"scale"
.LASF29:
	.string	"_IO_read_ptr"
.LASF25:
	.string	"size_t"
.LASF137:
	.string	"liner_search"
.LASF130:
	.string	"button"
.LASF106:
	.string	"pointer_x"
.LASF107:
	.string	"pointer_y"
.LASF47:
	.string	"_shortbuf"
.LASF152:
	.string	"init"
.LASF10:
	.string	"long int"
.LASF65:
	.string	"_IO_2_1_stderr_"
.LASF35:
	.string	"_IO_buf_base"
.LASF27:
	.string	"long long unsigned int"
.LASF22:
	.string	"glutBitmapHelvetica10"
.LASF23:
	.string	"glutBitmapHelvetica12"
.LASF86:
	.string	"neck_angle"
.LASF24:
	.string	"glutBitmapHelvetica18"
.LASF26:
	.string	"long long int"
.LASF2:
	.string	"signed char"
.LASF101:
	.string	"Vector"
.LASF111:
	.string	"cam_height"
.LASF69:
	.string	"sys_nerr"
.LASF42:
	.string	"_fileno"
.LASF20:
	.string	"glutBitmapTimesRoman10"
.LASF30:
	.string	"_IO_read_end"
.LASF151:
	.string	"shaking"
.LASF79:
	.string	"__timezone"
.LASF131:
	.string	"state"
.LASF64:
	.string	"_IO_2_1_stdout_"
.LASF34:
	.string	"_IO_write_end"
.LASF28:
	.string	"_flags"
.LASF36:
	.string	"_IO_buf_end"
.LASF142:
	.string	"projection"
.LASF83:
	.string	"bucket"
.LASF6:
	.string	"GLfloat"
.LASF8:
	.string	"double"
.LASF44:
	.string	"_old_offset"
.LASF150:
	.string	"idle"
.LASF139:
	.string	"TargetX"
.LASF5:
	.string	"GLsizei"
.LASF144:
	.string	"count"
.LASF119:
	.string	"Mode"
.LASF95:
	.string	"WALK"
.LASF82:
	.string	"timezone"
.LASF88:
	.string	"duration"
.LASF90:
	.string	"matrix"
.LASF117:
	.string	"LINE"
.LASF105:
	.string	"winH"
.LASF58:
	.string	"_IO_marker"
.LASF66:
	.string	"stdin"
.LASF18:
	.string	"glutBitmap9By15"
.LASF15:
	.string	"GLUquadricObj"
.LASF104:
	.string	"winW"
.LASF9:
	.string	"long unsigned int"
.LASF62:
	.string	"_IO_FILE_plus"
.LASF138:
	.string	"getWorldCood"
.LASF33:
	.string	"_IO_write_ptr"
.LASF146:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -fsanitize=leak -fstack-protector-strong"
.LASF60:
	.string	"_sbuf"
.LASF4:
	.string	"short unsigned int"
.LASF61:
	.string	"_pos"
.LASF132:
	.string	"keyboard"
.LASF91:
	.string	"p_speed"
.LASF37:
	.string	"_IO_save_base"
.LASF147:
	.string	"main.c"
.LASF94:
	.string	"camera"
.LASF48:
	.string	"_lock"
.LASF17:
	.string	"glutStrokeMonoRoman"
.LASF43:
	.string	"_flags2"
.LASF55:
	.string	"_mode"
.LASF67:
	.string	"stdout"
.LASF135:
	.string	"color"
.LASF103:
	.string	"line_vec_num"
.LASF112:
	.string	"cam_angle"
.LASF63:
	.string	"_IO_2_1_stdin_"
.LASF128:
	.string	"motion"
.LASF72:
	.string	"optarg"
.LASF49:
	.string	"_offset"
.LASF73:
	.string	"optind"
.LASF141:
	.string	"modelview"
.LASF93:
	.string	"cats"
.LASF115:
	.string	"CARRY"
.LASF100:
	.string	"PICKED"
.LASF149:
	.string	"_IO_lock_t"
.LASF57:
	.string	"_IO_FILE"
.LASF145:
	.string	"array1"
.LASF11:
	.string	"__off_t"
.LASF71:
	.string	"__environ"
.LASF78:
	.string	"__daylight"
.LASF7:
	.string	"float"
.LASF123:
	.string	"rgb_pm"
.LASF70:
	.string	"sys_errlist"
.LASF40:
	.string	"_markers"
.LASF114:
	.string	"BREED"
.LASF19:
	.string	"glutBitmap8By13"
.LASF1:
	.string	"unsigned char"
.LASF140:
	.string	"TargetY"
.LASF108:
	.string	"objX"
.LASF109:
	.string	"objY"
.LASF110:
	.string	"objZ"
.LASF3:
	.string	"short int"
.LASF116:
	.string	"COLOR"
.LASF41:
	.string	"_chain"
.LASF46:
	.string	"_vtable_offset"
.LASF80:
	.string	"tzname"
.LASF120:
	.string	"mode_name"
.LASF75:
	.string	"optopt"
.LASF21:
	.string	"glutBitmapTimesRoman24"
.LASF81:
	.string	"daylight"
.LASF113:
	.string	"WATCH"
.LASF13:
	.string	"char"
.LASF121:
	.string	"mode"
.LASF0:
	.string	"unsigned int"
.LASF96:
	.string	"JUMP"
.LASF126:
	.string	"argc"
.LASF74:
	.string	"opterr"
.LASF99:
	.string	"TURN"
.LASF59:
	.string	"_next"
.LASF12:
	.string	"__off64_t"
.LASF87:
	.string	"task"
.LASF45:
	.string	"_cur_column"
.LASF31:
	.string	"_IO_read_base"
.LASF39:
	.string	"_IO_save_end"
.LASF133:
	.string	"reshape"
.LASF50:
	.string	"__pad1"
.LASF51:
	.string	"__pad2"
.LASF52:
	.string	"__pad3"
.LASF53:
	.string	"__pad4"
.LASF54:
	.string	"__pad5"
.LASF134:
	.string	"display"
.LASF16:
	.string	"glutStrokeRoman"
.LASF56:
	.string	"_unused2"
.LASF68:
	.string	"stderr"
.LASF127:
	.string	"argv"
.LASF125:
	.string	"line_flg"
.LASF97:
	.string	"STAY"
.LASF14:
	.string	"GLUquadric"
.LASF76:
	.string	"signgam"
.LASF84:
	.string	"paint"
.LASF148:
	.string	"/home/k-kojima/git/jishupro/glview"
.LASF38:
	.string	"_IO_backup_base"
.LASF118:
	.string	"FUSION"
.LASF129:
	.string	"mouse"
.LASF124:
	.string	"pick_obj"
.LASF89:
	.string	"face"
.LASF122:
	.string	"rgb_flg"
.LASF92:
	.string	"MatArray"
.LASF143:
	.string	"viewport"
.LASF102:
	.string	"line_vector"
.LASF77:
	.string	"__tzname"
.LASF136:
	.string	"main"
.LASF32:
	.string	"_IO_write_base"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
