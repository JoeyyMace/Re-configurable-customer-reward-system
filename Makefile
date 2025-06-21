# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Source and object files
SRC = mainfile.cpp customers.cpp globals.cpp products.cpp transactions.cpp utility.cpp
INC = customers.h globals.h products.h transactions.h utility.h
OBJ = $(SRC:.cpp=.o)
TARGET = app

# Default rule to build the target
all: $(TARGET)

# Rule to link object files and create executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp $(INC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Optional: Rule to run the program
run: all
	./$(TARGET)

# Phony targets
.PHONY: all clean run

