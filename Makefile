CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -MMD -MP

# List of executables
TARGETS = main_node main_tree 

# Source files
SRCS1 = main_node.cpp node.cpp utils.cpp tree.cpp tree_reader.cpp
SRCS2 = main_tree.cpp node.cpp tree.cpp utils.cpp

# Object files (Replace .cpp with .o)
OBJS1 = $(SRCS1:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)

# Dependency files (Replace .cpp with .d)
DEPS1 = $(SRCS1:.cpp=.d)
DEPS2 = $(SRCS2:.cpp=.d)

# Default rule (build all programs)
all: $(TARGETS)

# Rule for program1
main_node: $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS1)

# Rule for program2
main_tree: $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS2)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files (.d files)
-include $(DEPS1) $(DEPS2)

# Clean build files
clean:
	rm -f $(TARGETS) *.o *.d
