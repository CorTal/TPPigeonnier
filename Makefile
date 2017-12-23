CFLAGS=-Wall -std=c++11
OFLAGS=-O2

SRC_DIR = ./src
BIN_DIR = ./bin

all: clean initialiser compiler_solver compiler_psolver

initialiser: 
	mkdir -p $(BIN_DIR)

compiler_solver: $(BIN_DIR)/solver.exe

$(BIN_DIR)/solver.exe: $(SRC_DIR)/solver.cpp
	g++ -o $@ $^ $(CFLAGS) $(OFLAGS)

solver:
	./$(BIN_DIR)/solver.exe	


compiler_psolver: $(BIN_DIR)/psolver.exe

$(BIN_DIR)/psolver.exe: $(SRC_DIR)/psolver.cpp
	g++ -o $@ $^ $(CFLAGS) $(OFLAGS) -fopenmp

psolver:
	./$(BIN_DIR)/psolver.exe	




clean:
	rm -f $(BIN_DIR)/*.exe
