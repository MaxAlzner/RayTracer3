CC = g++
CFLAGS = -Wall

INCDIR = include
SRCDIR = src
BINDIR = bin
OBJDIR = obj
INC = $(wildcard $(INCDIR)/*.*)
SRC = $(wildcard $(SRCDIR)/*.*)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
LIB = -lshape -lfreeimage
LIB += -lncurses

TARGET = $(BINDIR)/raytracer

$(TARGET): compile
	@echo "Building"
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LIB)
	@cp -f ./MANUAL $(BINDIR)
	@cp -f ./LICENSE $(BINDIR)

.PHONY: compile
compile:
	@echo "Compiling"
	@mkdir -p $(OBJDIR)
	@$(foreach target,$(SRC),echo $(target);$(CC) -c -o $(subst $(SRCDIR)/,$(OBJDIR)/,$(subst .cpp,.o,$(target))) $(target) $(CFLAGS);)

.PHONY: clean
clean:
	@echo "Cleaning"
	@rm -rf $(OBJDIR)
	@rm -rf $(BINDIR)

.PHONY: testdata
testdata:
	@cp -f data/*.* ~/.raytracer