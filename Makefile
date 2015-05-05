all: fakerm fakeshred

fakerm: fakerm.c
	gcc -Wall -o $@ $^

fakeshred: fakeshred.c
	gcc -Wall -o $@ $^

install:
	mkdir -p ~/bin
	cp fakerm ~/bin/rm
	cp fakeshred ~/bin/shred
