# Simple Makefile to build PolyCARP library and example application

SRC0   = $(wildcard src/*.cpp)
SRCS   = $(SRC0:src/PolycarpExample.cpp=)
OBJS   = $(SRCS:.cpp=.o)
INCLUDEFLAGS = -Iinclude 
LINKFMT = -lfmt
CXXFLAGS = $(INCLUDEFLAGS) -Wall -O 

all: lib example

lib: $(OBJS)
	@echo 
	@echo "** Building PolyCARP binary library"
	ar -cr lib/PolyCARP.a $(OBJS) && ranlib lib/PolyCARP.a #&& rm *.o
	@echo 

example:
	@echo
	@echo "** Building DaidalusExample application"
	$(CXX) -o PolycarpExample $(CXXFLAGS) src/PolycarpExample.cpp lib/PolyCARP.a
	@echo 
	@echo "** To run PolycarpExample type:"
	@echo "./PolycarpExample"

polycarpdetect: lib
	@echo
	@echo "** Building Polycarp detection example"
	$(CXX) -o PolycarpDetection $(CXXFLAGS) src/PolycarpDetectionExample.cpp $(LINKFMT) lib/PolyCARP.a 

clean:
	rm -f PolycarpExample PolycarpDetectionExample $(OBJS) lib/PolyCARP.a 

.PHONY: all lib example
