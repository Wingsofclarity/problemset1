main: test.c
	gcc -Wall -std=c11 test.c -o main

run: main
	./main

test: run
	cat data

clean:
	@rm -f *~
