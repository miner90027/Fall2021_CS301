section .text
	global getHealth
	global inventoryPtr
	global attack
	global useItem
	global resetEnemy
	global enemyHealth
	global receiveItem

	getHealth:
		mov rax, QWORD[playerPtr +8*0]
		ret

	enemyHealth:
		mov rax, enemyPtr
		ret

	resetEnemy:
		xor rax, rax
		mov QWORD[enemyPtr+8*0], rdi
		mov QWORD[enemyPtr+8*1], rsi
		ret

	useItem:							;receives int/long as input to determine index in mem
		xor rax, rax				;reset registers
		xor rcx, rcx
		
		cmp rdi, 0					;Verify valid index - works
		jl .invalid
		cmp rdi, 5
		jge .invalid
		
		;mov rcx, rdi
		
		mov rcx, QWORD[inventoryPtr +8* rdi]
		
		cmp rcx, 1
		je .potion
		cmp rcx, 2
		je .sword
		cmp rcx, 3
		je .dagger
		cmp rcx, 4
		je .bottle
		ret
		
		.potion:
			mov QWORD[playerPtr +8*0], 100
			mov QWORD[inventoryPtr +8* rdi], 4
			mov rax, rcx
			ret
			
		.sword:
			mov QWORD[playerPtr +8*1], 20
			mov rax, rcx
			ret
			
		.dagger:
			mov QWORD[playerPtr +8*1], 5
			mov rax, rcx
			ret
		
		.bottle:
			cmp QWORD[playerPtr +8*0], 100
			je .used
			add QWORD[playerPtr +8*0], 10
				.used:
			mov QWORD[inventoryPtr +8* rdi], 0
			mov rax, rcx
			ret
			
		.invalid:
			mov rax, -1
			ret

		attack:
		cmp rdi, 0
		jne .hitPlayer
		
		.hitEnemy:
			mov rcx, [playerPtr+8*1]
			sub [enemyPtr+8*0], rcx
			cmp QWORD[enemyPtr+8*0], 0
			jle .end
			jmp enemyHealth
		
		.hitPlayer:
			mov rcx, [enemyPtr+8*1]
			sub [playerPtr+8*0], rcx
			cmp QWORD[playerPtr+8*0], 0
			jle .end
			jmp getHealth
			
			.end:
				xor rax, rax
				ret

	receiveItem:
	xor rax, rax
	mov rax, -1
	xor rcx, rcx
	
	.loop:
		mov rdx, QWORD[inventoryPtr +8*rcx]
		cmp rdx, 0
		je .checkVal
		
		add rcx, 1
		cmp rcx, 5
		jl .loop
		ret
	
	.checkVal:
		cmp rdi, 1
		je .store
		cmp rdi, 2
		je .store
		cmp rdi, 3
		je .store
		
		mov rax, 1
		ret
	
	.store:
		mov QWORD[inventoryPtr +8*rcx], rdi
		xor rax, rax
		ret
	
section .data
playerPtr:
	dq 100	; Health
	dq 5      ; Attack
	
enemyPtr:
	dq 0    ; Health
	dq 1     ; Attack

inventoryPtr:
	dq 0
	dq 0
	dq 0
	dq 0
	dq 0

