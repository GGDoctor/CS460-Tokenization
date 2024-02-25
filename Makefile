# Compiler
CC = g++

# Source files
SRCS = Tokenization.cpp

# Object files
OBJS = Tokenization.o

# Executable file
MAIN = Tokenization

# Build rule for the executable
$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS)

# Rule for building .o files from .cpp files
.cpp.o:
	$(CC) -c $< -o $@

# Clean rule
clean:
	$(RM) *.o *~ $(MAIN)

# Dependency generation rule
depend: $(SRCS)
	makedepend $^

# DO NOT DELETE THIS LINE -- make depend needs it
