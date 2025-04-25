#change names to files when we get that far

INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := dsw.o avlHash.o binomial.o final.o hash.o mainFinal.o
DEPS 		 := ${INCLUDE_DIRS}/dsw.h ${INCLUDE_DIRS}/binomial.h ${INCLUDE_DIRS}/avlHash.h ${INCLUDE_DIRS}/final.h ${INCLUDE_DIRS}/hash.h

.PHONY: clean all

all: dsw.o avlHash.o binomial.o final.o hash.o mainFinal.o finalrun

clean:
	rm $(OBJS) finalrun


dsw.o: dsw.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

avlHash.o: avlHash.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<
	
final.o: final.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

binomial.o: binomial.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<	

hash.o: hash.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<		

mainFinal.o: mainFinal.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

finalrun: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)