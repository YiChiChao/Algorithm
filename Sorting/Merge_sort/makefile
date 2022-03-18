CC = gcc
CFLAGS = -g -Wall
OBJECT = project
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

OBJS = merge.o
BINS = Testmerge
all: $(BINS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BINS): $(BINS).c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@


do: 
	./$(BINS)

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(BINS)

clean:
	rm $(BINS) $(OBJS)