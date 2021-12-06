section .text
	global getHealth
	global inventoryPtr
	global playerPtr
	global attack
	global useItem
	
	getHealth:
		mov rax, QWORD[playerPtr +8*0]
		ret
		
	enemyHealth:
		mov rax, QWORD[enemyPtr +8*0]
		ret
	
	resetEnemy:
		xor rax, rax
		mov QWORD[enemyPtr+8*0], 50
		mov QWORD[enemyPtr+8*1], 1
		ret
		
	useItem:							;receives int/long as input to determine index in mem
		xor rax, rax				;reset registers
		xor rcx, rcx
		
		cmp rdi, 0					;Verify valid index - works
		jl .invalid
		cmp rdi, 5
		jge .invalid
		
		;mov rcx, rdi
		
		mov rcx, QWORD[inventoryPtr +8* rdi]		;store value @ index into register
		;mov rax, rcx			;tests to verify that geting correct value from array
		;ret
		
		cmp rcx, 1				;compare value in mem to possible values & jmp to code
		je .potion				;none of the cmps ever = true
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
			jne .used
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
	
section .data
playerPtr:
	dq 100	; Health
	dq 1      ; Attack
	
enemyPtr:
	dq 50    ; Health
	dq 1     ; Attack

inventoryPtr:
	dq 0
	dq 0
	dq 0
	dq 0
	dq 0

