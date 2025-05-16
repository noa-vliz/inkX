# Compiler and flags settings
CC     := clang
CFLAGS := -Wall -Wextra -std=c99 -O2 -Iinclude
LDLIBS := -lX11

# Directory settings
SRCDIR  := src
OBJDIR  := deps/object
BINDIR  := bin
TARGET  := $(BINDIR)/cgt

# Auto-detect source files
SOURCES := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Default targets
.PHONY: all clean 

all: $(TARGET)

# Create binary (linking)
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $^ -o $@ $(LDLIBS)

# Create object files (compilation)
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# Cleanup
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(BINDIR)
	@rm -rf deps
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
	@echo "Dependencies:"
	@echo $(OBJECTS)

# Help
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove generated files"
	@echo "  rebuild   - Clean and then build"
	@echo "  debug     - Debug build"
	@echo "  release   - Release build"
	@echo "  deps      - Show dependencies"
	@echo "  help      - Show this help"
