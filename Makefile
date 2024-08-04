CC=gcc

ODIR=build

music: main.c build
	$(CC) -o ./build/music -I./inc main.c ./src/music.c

# music.c:
	# $(CC) -o ./build/music.o -I./inc ./src/music.c

build:
	mkdir -p build
