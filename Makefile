## ----------- start of compilation -----------
CXX := icc 
CXXFLAGS := -std=c++11 -fopenmp -O3 -I.
DEPS := $(wildcard *.hpp)
Obj := butterfly.o

all: butterfly.bin

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

butterfly.bin: $(Obj)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm *.o

cleandist:
	rm *.o butterfly.bin
