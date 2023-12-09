CXX = g++
CXXFLAGS=-std=c++20 -I/usr/local/include -fPIC
LDFLAGS=-L/usr/local/lib -lsimlib -static

# Automatically find all .cpp files in the directory
SOURCES := $(wildcard *.cpp)

# Replace the .cpp extension with .o for object files
OBJECTS := $(SOURCES:.cpp=.o)

# The final build target
all: program

# Rule for building the final program
program: $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) -o $@

# Rule for building object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm *.o

run: program
	./program -p 1000