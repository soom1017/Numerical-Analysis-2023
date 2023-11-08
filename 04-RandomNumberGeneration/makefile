SRC_DIR = ../NRs/ansi/recipes
OTHER_DIR = ../NRs/ansi/other
SRCS = main.c $(SRC_DIR)/ran1.c $(SRC_DIR)/gasdev.c

rnbGen : $(SRCS) ../NRs/ansi/other/nr.h
	cc -o rnbGen $(SRCS)

clean: 
	rm -f rnbGen