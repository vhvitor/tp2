MAIN = ./main
MAIN_DIR = /Main
BIN =./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src
RELEASE = /Release
DEBUG = /Debug

RUN = ./bin/Main

FLAGS = -O3 -Wall
LIBS = -led -L $(LIB)

all: \
	libed \
	mymain


# SRC compile
libed: \
	$(OBJ)$(RELEASE)/patient.o \
	$(OBJ)$(RELEASE)/exam.o \
	$(OBJ)$(RELEASE)/doublylinkedlist.o \
	$(OBJ)$(RELEASE)/arrivalsimulation.o \
	$(OBJ)$(RELEASE)/dispatcher.o \
	$(OBJ)$(RELEASE)/filehandler.o \
	$(OBJ)$(RELEASE)/eventmanager.o \
	$(OBJ)$(RELEASE)/exampriorityqueue.o \
	$(OBJ)$(RELEASE)/genericqueue.o \
	$(OBJ)$(RELEASE)/report.o \
	$(OBJ)$(RELEASE)/rxmachinesimulation.o

	ar -rcs $(LIB)/libed.a $(OBJ)$(RELEASE)/*.o


# Main compile
mymain: clean_main

	$(BIN)$(MAIN_DIR)/main

$(OBJ)$(RELEASE)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)$(MAIN_DIR)/%: $(MAIN)/%.c
	gcc $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@

run:
	$(RUN)/main

clean:
	rm -rf $(BIN)$(DEBUG)/* $(BIN)$(RELEASE)/* $(OBJ)$(DEBUG)/* $(OBJ)$(RELEASE)/* $(LIB)/*

clean_main:
	rm -rf $(BIN)$(MAIN_DIR)/*
