CXXSOURCE = expr.o cmdline.o tests.o  main.o
CXXFLAGS = --std=c++14
HEADERS = expr.h cmdline.h catch.h
EXECUTABLE = ./build

all: $(EXECUTABLE)
	
all: build
build: $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) -o build $(CXXSOURCE)
	
expr.o: expr.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c expr.cpp
	
cmdline.o: cmdline.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c cmdline.cpp

tests.o: tests.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c tests.cpp
	
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

.PHONY: clean printM
clean:
	rm -f *.o *.out program
printM:
	echo $(CXXSOURCE)

