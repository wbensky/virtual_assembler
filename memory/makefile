# this is a makefile of the c++ project main
# the standard c compiler on GNU linux is g++
# written by wben on November 14th, 2013

                    TARGET = .

                        GCC = g++
                     CFLAGS = -g -Wall
                     CFLAGC = -c

                        SRC = memory_manage.cpp \
                              test.cpp
                       OBJS = memory_manage.o \
                              test.o
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
