CC = gcc 
CFLAGS = -Wall -g 
OBJS = main.o parser.o 

all: $(OBJS)
	$(CC) $(CFLAGS) -o qsim $(OBJS)  

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o qsim
