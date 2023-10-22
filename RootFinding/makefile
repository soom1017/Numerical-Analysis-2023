SRC_DIR = ../NRs/ansi/recipes
OTHER_DIR = ../NRs/ansi/other
SRCS = main.c $(OTHER_DIR)/nrutil.c $(SRC_DIR)/bessj0.c $(SRC_DIR)/bessj1.c $(SRC_DIR)/zbrak.c $(SRC_DIR)/rtbis.c $(SRC_DIR)/rtflsp.c $(SRC_DIR)/rtsec.c $(SRC_DIR)/rtnewt.c $(SRC_DIR)/rtsafe.c muller.c nonlinear_func.c

rootFinding : $(SRCS) ../NRs/ansi/other/nr.h muller.h nonlinear_func.h
	cc -o rootFinding $(SRCS) -I ../NRs/ansi/other

clean: 
	rm -f rootFinding
