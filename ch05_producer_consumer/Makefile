src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = -g

myprog: $(obj)
	$(CC) -pthread -lrt -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog
