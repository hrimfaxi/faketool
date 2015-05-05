all: fakerm fakeshred

fakerm: fakerm.c common.c
	gcc -Wall -o $@ $^

fakeshred: fakeshred.c common.c
	gcc -Wall -o $@ $^

install:
	mkdir -p ~/bin
	cp fakerm ~/bin/rm
	cp fakeshred ~/bin/shred

clean:
	rm -f *.o *~ fakerm fakeshred
