; player.asm
; Aleks McCormick
; 2021/12/02
; Fall 2021 CS 301
; Final Project 
; Simple Text based RPG using asm
; Assembly functions

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

	score:							; Returns the Player's current score
		mov rax, QWORD[playerPtr +8*2]
		ret
	
	gainXP:							; Adds the enemy's xp drop amount to the Player's score
		xor rax, rax
		mov rdx, QWORD[enemyPtr+8*2]
		add QWORD[playerPtr +8*2], rdx
		ret
	
	
	getHealth:						; Returns the Player's health
		mov rax, QWORD[playerPtr +8*0]
		ret

	enemyHealth:					; Returns the Enemy's health
		mov rax, QWORD[enemyPtr +8*0]
		ret

	resetEnemy:						; Sets the enemy health, attack, & drop XP to the input values
		xor rax, rax
		mov QWORD[enemyPtr+8*0], rdi
		mov QWORD[enemyPtr+8*1], rsi
		mov QWORD[enemyPtr+8*2], rdx
		ret

	useItem:						;receives int/long as input to determine index in mem
		xor rax, rax				;reset registers
		xor rcx, rcx
		
		cmp rdi, 0					;Verify valid index
		jl .invalid
		cmp rdi, 5
		jge .invalid
		
		mov rcx, QWORD[inventoryPtr +8* rdi]
		
		cmp rcx, 1					; Compare the item in the slot to the possible values
		je .potion					;		Preform actions accordingly
		cmp rcx, 2
		je .sword
		cmp rcx, 3
		je .dagger
		cmp rcx, 4
		je .bottle
		ret
		
		.potion:					; Heal player to full & replace potion with bottle
			mov QWORD[playerPtr +8*0], 100
			mov QWORD[inventoryPtr +8* rdi], 4
			mov rax, rcx
			ret
			
		.sword:						; Set player attack to 20
			mov QWORD[playerPtr +8*1], 20
			mov rax, rcx
			ret
			
		.dagger:					; Set Player attack to 10
			mov QWORD[playerPtr +8*1], 10
			mov rax, rcx
			ret
		
		.bottle:					; Heal player by 10 untill full, empty slot after use
			cmp QWORD[playerPtr +8*0], 100
			je .used
			add QWORD[playerPtr +8*0], 10
				.used:
			mov QWORD[inventoryPtr +8* rdi], 0
			mov rax, rcx
			ret
			
		.invalid:					; Return -1 to signify invalid input
			mov rax, -1
			ret

		attack:						; Attack based on input value, returns damage delt
		xor rax, rax
		cmp rdi, 0					; compare input to 0, not 0 -> enemy attacks player
		jne .hitPlayer
		
		.hitEnemy:					; Player attacks enemy
			mov rax, [playerPtr+8*1]
			sub [enemyPtr+8*0], rax
			ret
		
		.hitPlayer:					; Enemy attacks Player
			mov rax, [enemyPtr+8*1]
			sub [playerPtr+8*0], rax
			ret


	receiveItem:					; Store the given item in the next empty inventory slot
		xor rax, rax
		mov rax, -1					; Default return value signifies full inventory
		xor rcx, rcx
		
		.loop:						; Loop through inventory until an empty slot is found
			mov rdx, QWORD[inventoryPtr +8*rcx]
			cmp rdx, 0
			je .checkVal
			
			add rcx, 1
			cmp rcx, 5
			jl .loop
			ret
		
		.checkVal:					;Verify that a valid item is being stored
			cmp rdi, 1
			je .store
			cmp rdi, 2
			je .store
			cmp rdi, 3
			je .store
			
			mov rax, 1
			ret
		
		.store:						; Store item in open inventory slot
			mov QWORD[inventoryPtr +8*rcx], rdi
			xor rax, rax
			ret

section .data
playerPtr:
	dq 100		; Health
	dq 5		; Attack
	dq 0		; Score
	
enemyPtr:
	dq 0		; Health
	dq 0		; Attack
	dq 0		; XP drop amount

inventoryPtr:
	dq 0,0,0,0,0

