# utils makefile
# 2021-09-25 20:50
# by Ian D Brunton <iandbrunton at gmail dot com>

CC = gcc

APPS = c2f f2c inc kg2lb lb2kg odo roundtime watermark
CFLAGS = -I.
LDFLAGS =

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

c2f: 
	$(CC) -o c2f c2f.c $(CFLAGS)

f2c:
	$(CC) -o f2c f2c.c $(CFLAGS)

inc: 
	$(CC) -o inc inc.c $(CFLAGS)

kg2lb:
	$(CC) -o kg2lb kg2lb.c $(CFLAGS)

lb2kg:
	$(CC) -o lb2kg lb2kg.c $(CFLAGS)

odo:
	$(CC) -o odo odo.c $(CFLAGS)

roundtime:
	$(CC) -o roundtime roundtime.c $(CFLAGS)

watermark:
	$(CC) -o watermark watermark.c $(CFLAGS)

clean:
	rm -rf *.o
