CC=gcc
CFLAGS=-Wall -g

all: vuln

vuln: main.o utils.o
	$(CC) $(CFLAGS) -o vuln main.o utils.o

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o vuln _codeql_detected_source_root
