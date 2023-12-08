SRC_DIR = ../NRs/ansi/recipes
OTHER_DIR = ../NRs/ansi/other
SRCS = main.c $(OTHER_DIR)/nrutil.c $(SRC_DIR)/gaussj.c

dataFit : $(SRCS) ../NRs/ansi/other/nr.h
	cc -o dataFit $(SRCS) -I $(OTHER_DIR)

clean: 
	rm -f dataFit