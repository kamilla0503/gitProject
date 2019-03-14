CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-O3 -std=c++11 
LDFLAGS=-O3 -std=c++11 
LDLIBS=

SRCS=ncs.cpp \
     classes.cpp \
     blockfinder.cpp \
     scheme.cpp \
     blockfinder_main.cpp \
     PatternCodes.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
all: blockfinder

ncs.o: ncs.cpp ncs.h

classes.o: classes.cpp ncs.h

blockfinder.o: blockfinder.cpp blockfinder.h ncs.h

blockfinder_main.o: blockfinder_main.cpp blockfinder.h ncs.h

scheme.o: scheme.cpp scheme.h

PatternCodes.o: PatternCodes.cpp PatternCodes.h

blockfinder: $(OBJS)
	$(CXX) $(LDFLAGS) -o blockfinder $(OBJS) $(LDLIBS)

test:
	./test_ncs

clean:
	$(RM) $(OBJS) test_ncs
