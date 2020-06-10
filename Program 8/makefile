# Makefile for the Crypto Assignment

# These variables control the specifics of the compilation
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O1
OBJECTS = Crypto.o Checksum.o Key.o
EXEC = Crypto

# Default
${EXEC} : ${OBJECTS}
	${CC} ${OBJECTS} -o ${EXEC}

# Rule to build Crypto executable
Crypto.o : Crypto.c Key.h Checksum.h
	${CC} ${CFLAGS} -c Crypto.c

# Rule to build Key executable
Key.o : Key.c Key.h Checksum.h
	${CC} ${CFLAGS} -c Key.c

# Rule to build Checksum executable
Checksum.o : Checksum.c Checksum.h
	${CC} ${CFLAGS} -c Checksum.c

# Execute tests
run: Crypto
	./Crypto

# Clean all executable files
clean:
	rm -f ${EXEC} ${OBJECTS}
