# this is a makefile of the c++ project main
# the standard c compiler on GNU linux is g++
# written by wben on November 25th, 2013

                    TARGET = .

                        GCC = g++ -std=c++11
                     CFLAGS = -g -Wall
                     CFLAGC = -c

                        SRC = ../compile/compile.cpp \
                              main.cpp \
							  ../instruction/instruction_binary.cpp \
							  ../register/register_definition.cpp                       
						OBJS = compile.o \
                              main.o \
							  instruction_binary.o \
							  register_definition.o
                       EXEC = main

                    INCLUDE = 
                       LIBS = 

all: $(EXEC)

$(EXEC): $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) $(LIBS) -o $@
	rm -f $(OBJS)

$(OBJS): $(SRC)
	$(GCC) $(CFLAGC) $(SRC) $(INCLUDE)

install:
	cp $(EXEC) /usr/local/bin

uninstall:
	rm -f /usr/local/bin/$(EXEC)

clean:
	rm -f $(EXEC)
