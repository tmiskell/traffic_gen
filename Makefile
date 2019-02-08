src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lpthread -lcurl

trafficgen: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(obj) trafficgen
