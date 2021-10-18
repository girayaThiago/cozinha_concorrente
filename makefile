CC=g++
EXECNAME = cozinha.out
SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = object
CFLAGS = -std=c++17
LFLAGS = -lpthread

BIN = $(BINDIR)/$(EXECNAME)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

run: all
	./cozinha.out

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(EXECNAME)

%.o: $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@)
	$(CC) $(CFLAGS) -c $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) -o $@

clean:
	rm -f $(OBJ) *~
