g++ -c main.cpp
nasm -f elf64 player.asm
nasm -f elf64 room.asm
g++ -no-pie -o run main.o player.o room.o
