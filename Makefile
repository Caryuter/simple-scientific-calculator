CC= gcc
OBJS = main.o basics.o basics_int.o main_IO.o misc_op.o tests.o utils.o
CFLAGS = 
LDFLAGS = -lm

all: exec

exec: $(OBJS)
	$(CC) -o $@ $? $(LDFLAGS)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< 

clean: 
	rm -f programa $(OBJS)
	rm -f exec
