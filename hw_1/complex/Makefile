# Compilers
CC          := g++ -std=c++17
DGEN        := doxygen

# The Target Binary Program
TARGET      := test

# The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := .
INCDIR      := .
BUILDDIR    := ./build
TARGETDIR   := ./bin
SRCEXT      := c
GTEST_DIR   := /opt/homebrew/Cellar/googletest/1.15.2

# Flags, Libraries, and Includes
CFLAGS      := -g
LIB         := -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread -lm
INC         := -I$(INCDIR) -I$(GTEST_DIR)/include

# Files
DGENCONFIG  := docs.config
HEADERS     := complex.h
SOURCES     := complex.c unit_tests.c main.c
OBJECTS     := $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCES)))

# Default Make
all: directories $(TARGETDIR)/$(TARGET)

# Remake
remake: spotless all

# Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

# Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)/*.o

# Full Clean, Objects, and Binaries
spotless: clean
	@$(RM) -rf $(TARGETDIR)/$(TARGET) $(DGENCONFIG)

# Link
$(TARGETDIR)/$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $(OBJECTS) $(LIB)

# Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: directories remake clean spotless
