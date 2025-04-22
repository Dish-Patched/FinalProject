#change names to files when we get that far

INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := customErrorClass.o blank.o main.o
DEPS 		 := ${INCLUDE_DIRS}/customErrorClass.h ${INCLUDE_DIRS}/binomial.h ${INCLUDE_DIRS}/blank.h

.PHONY: clean all

all: customErrorClass.o binomial.o main.o blankrun

clean:
	rm $(OBJS) blankrun


customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

avl.o: avl.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

blankrun: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)