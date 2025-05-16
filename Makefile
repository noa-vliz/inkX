# Compiler and flags settings
CC     := clang
CFLAGS := -Wall -Wextra -std=c99 -O2 -Iinclude
LDLIBS := -lX11

# Directory settings
SRCDIR     := src
OBJDIR     := deps/object
LIBDIR     := lib
EXAMPLEDIR := example
BINDIR     := bin

# Library settings
LIBNAME    := libinkX
STATIC_LIB := $(LIBDIR)/$(LIBNAME).a
SHARED_LIB := $(LIBDIR)/$(LIBNAME).so

# Auto-detect source files (exclude any example files that might be in src)
LIB_SOURCES := $(filter-out %/example.c,$(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c))
LIB_OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(LIB_SOURCES))

# Auto-detect example files
EXAMPLE_SOURCES := $(wildcard $(EXAMPLEDIR)/*.c)
EXAMPLE_OBJECTS := $(patsubst $(EXAMPLEDIR)/%.c,$(OBJDIR)/example_%.o,$(EXAMPLE_SOURCES))
EXAMPLE_TARGETS := $(patsubst $(EXAMPLEDIR)/%.c,$(BINDIR)/%,$(EXAMPLE_SOURCES))

# Default targets
.PHONY: all lib examples clean install

all: lib examples

# Build library
lib: $(STATIC_LIB) $(SHARED_LIB)

# Build examples
examples: $(EXAMPLE_TARGETS)

# Create directories if needed (these are implicit now via mkdir -p above)
#$(OBJDIR):
#	@mkdir -p $(OBJDIR)
#
#$(LIBDIR):
#	@mkdir -p $(LIBDIR)
#
#$(BINDIR):
#	@mkdir -p $(BINDIR)

# Create static library
$(STATIC_LIB): $(LIB_OBJECTS)
	@mkdir -p $(LIBDIR)
	@echo "Creating static library: $@"
	ar rcs $@ $^
	ranlib $@

# Create shared library
$(SHARED_LIB): $(LIB_OBJECTS)
	@mkdir -p $(LIBDIR)
	@echo "Creating shared library: $@"
	$(CC) -shared $^ -o $@ $(LDLIBS)

# Create object files from library sources with -fPIC (for both static and shared libraries)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Create object files from example sources (no -fPIC needed for executables)
$(OBJDIR)/example_%.o: $(EXAMPLEDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling example $< to $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Create example executables
$(BINDIR)/%: $(OBJDIR)/example_%.o $(STATIC_LIB)
	@mkdir -p $(BINDIR)
	@echo "Building example: $@"
	$(CC) $< -L$(LIBDIR) -linkX $(LDLIBS) -o $@

# Install to system (optional)
install: $(STATIC_LIB) $(SHARED_LIB)
	@echo "Installing libraries to /usr/local/lib..."
	@sudo cp $(STATIC_LIB) /usr/local/lib/
	@sudo cp $(SHARED_LIB) /usr/local/lib/
	@echo "Installing headers to /usr/local/include..."
	@sudo cp -r include/* /usr/local/include/
	@echo "Updating linker cache..."
	@sudo ldconfig

# Cleanup
clean:
	@rm -rf $(OBJDIR) $(LIBDIR) $(BINDIR) deps
	@echo "Cleanup completed"

# Rebuild
rebuild: clean all

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: all

# Release build
release: CFLAGS += -O3 -DNDEBUG
release: all

# Show dependencies
deps:
	@echo "Library sources:"
	@echo $(LIB_SOURCES)
	@echo ""
	@echo "Library objects:"
	@echo $(LIB_OBJECTS)
	@echo ""
	@echo "Example sources:"
	@echo $(EXAMPLE_SOURCES)
	@echo ""
	@echo "Example targets:"
	@echo $(EXAMPLE_TARGETS)

# Test build (compile examples with debug info)
test: CFLAGS += -g -DDEBUG
test: examples

# Verbose compilation (for debugging)
verbose: CFLAGS += -v
verbose: all

# Help
help:
	@echo "Available targets:"
	@echo "  all       - Build library and examples (default)"
	@echo "  lib       - Build only the library (static and shared)"
	@echo "  examples  - Build only the examples"
	@echo "  clean     - Remove generated files"
	@echo "  rebuild   - Clean and then build all"
	@echo "  debug     - Debug build"
	@echo "  release   - Release build (optimized)"
	@echo "  test      - Build examples with debug info"
	@echo "  verbose   - Verbose compilation output"
	@echo "  install   - Install library to system (/usr/local)"
	@echo "  deps      - Show dependencies"
	@echo "  help      - Show this help"

# Show project structure
info:
	@echo "Project Structure:"
	@echo "  Library sources:  $(LIB_SOURCES)"
	@echo "  Example sources:  $(EXAMPLE_SOURCES)"
	@echo "  Static library:   $(STATIC_LIB)"
	@echo "  Shared library:   $(SHARED_LIB)"
	@echo "  Example targets:  $(EXAMPLE_TARGETS)"
