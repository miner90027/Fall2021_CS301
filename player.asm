section .text
	global getHealth
	global inventoryPtr
	global attack
	global useItem
	global resetEnemy
	global enemyHealth
	global receiveItem
	global score
	global gainXP

	score:
		mov rax, QWORD[playerPtr +8*2]
		ret
	
	gainXP:
		xor rax, rax
		mov rdx, QWORD[enemyPtr+8*2]
		add QWORD[playerPtr +8*2], rdx
		ret
	
	
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
		mov QWORD[enemyPtr+8*2], rdx
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
			mov rax, [playerPtr+8*1]
			sub [enemyPtr+8*0], rax
			ret
		
		.hitPlayer:
			mov rax, [enemyPtr+8*1]
			sub [playerPtr+8*0], rax
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
	dq 5		; Attack
	dq 0		; Score
	
enemyPtr:
	dq 0		; Health
	dq 0		; Attack
	dq 0		; XP drop amount

inventoryPtr:
	dq 0,0,0,0,0

