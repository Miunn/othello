CC = g++
CFLAGS = -Wall
LIB =
SDIR = src
HDIR = includes
BUILDDIR = bin
BINARY = main
CUSTOMLIBDIR = lib


# ==========================================================================

# listing all .cpp file inside SDIR and his child folder
SOURCES := $(foreach dir, $(wildcard $(SDIR)/*),$(wildcard $(dir)/*.cpp)) $(wildcard $(SDIR)/*.cpp)

# listing all .o file from all .cpp file from SDIR
OBJECTS := $(patsubst $(SDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

CUSTOMLIBS := $(wildcard $(CUSTOMLIBDIR)/*)

INCLUDELIB := $(foreach lib, $(CUSTOMLIBS), -I$(lib)/$(HDIR))

# ==========================================================================

all: $(BINARY) 

$(BINARY): $(OBJECTS) $(CUSTOMLIBS)/%.o
	$(CC) $(CFLAGS) $(OBJECTS) $(foreach lib, $(CUSTOMLIBS), $(wildcard $(lib)/*.o)) -o $@ $(LIB)

$(BUILDDIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(HDIR) $(INCLUDELIB) -c $< -o $@

$(CUSTOMLIBS)/%.o:
	$(foreach lib, $(CUSTOMLIBS),  (cd $(lib) && make))

full-clean: clean
	$(foreach lib, $(CUSTOMLIBS),  (cd $(lib) && make clean))

clean:
	rm -rf $(foreach dir,$(wildcard $(BUILDDIR)/*), $(dir)) $(BINARY)

# ==========================================================================