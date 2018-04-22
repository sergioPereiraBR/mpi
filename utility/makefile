CC = mpicc
CFLAGS = -g -Werror -lm -I. #-Wall -std=c99
SRC = ~/repgit/mpi/sc/tuto/hw/hw.c

EX = mpiexec
EXEC = hw
np = 2


run: $(EXEC)
	@echo " "
	@$(EX) -f hostfile -n $(np) ./$(EXEC)
	@echo " "

runt: $(EXEC)
	@echo " "
	@$(EX) -f hostfile -n $(np) time ./$(EXEC)
	@echo " "

$(EXEC): $(SRC)
	@$(CC) $^ -o $@ $(CFLAGS)
clean: $(EXEC)
	@rm -rf *.o
	@rm -rf $^
