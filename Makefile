all: fakerm fakeshred fakemake

fakerm: fakerm.c common.c
	gcc -Wall -o $@ $^

fakeshred: fakeshred.c common.c
	gcc -Wall -o $@ $^

fakemake: fakemake.c common.c
	gcc -Wall -o $@ $^

install:
	mkdir -p ~/bin
	cp fakerm ~/bin/rm
	cp fakeshred ~/bin/shred
	cp fakemake ~/bin/make

clean:
	rm -f *.o *~ fakerm fakeshred fakemake
