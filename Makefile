all:
	mkdir bin
	gcc main.c -o bin/main

clean:
	rm -r bin
