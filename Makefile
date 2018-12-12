all:
	mkdir bin
	gcc main.c -o bin/main -std=c99

clean:
	rm -r bin
