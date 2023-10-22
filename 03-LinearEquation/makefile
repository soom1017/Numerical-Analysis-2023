SRC_DIR = ../NRs/ansi/recipes
OTHER_DIR = ../NRs/ansi/other
SRCS = main.c $(OTHER_DIR)/nrutil.c $(SRC_DIR)/gaussj.c $(SRC_DIR)/ludcmp.c $(SRC_DIR)/lubksb.c $(SRC_DIR)/svdcmp.c $(SRC_DIR)/svbksb.c $(SRC_DIR)/pythag.c $(SRC_DIR)/mprove.c

linEq : $(SRCS) ../NRs/ansi/other/nr.h
	cc -o linEq $(SRCS) -I $(OTHER_DIR)

clean: 
	rm -f linEq