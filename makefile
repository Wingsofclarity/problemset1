comp: test.c
	@gcc -Wall -std=c11 test.c -o main

run: comp
	@./main

clean:
	@rm -f *~
