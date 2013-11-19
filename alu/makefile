# this is a makefile of the c++ project main
# the standard c compiler on GNU linux is g++
# written by wben on November 19th, 2013

                    TARGET = .

                        GCC = g++ -std=c++11
                     CFLAGS = -g -Wall
                     CFLAGC = -c

                        SRC = alu_manage.cpp \
                              alu_operate.cpp \
                              test.cpp\
							  ../register/register_operates.cpp
                       OBJS = alu_manage.o \
                              alu_operate.o \
                              test.o\
							  register_operates.o
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
