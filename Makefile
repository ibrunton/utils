# utils makefile
# 2021-09-25 20:50
# by Ian D Brunton <iandbrunton at gmail dot com>

CC = gcc

APPS = bvgas c2f f2c gas inc kg2lb lb2kg messages odo roundtime sr watermark
CFLAGS = -I.
LDFLAGS =

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

bvgas:
	$(CC) -o bvgas bvgas.c $(CFLAGS)
c2f: 
	$(CC) -o c2f c2f.c $(CFLAGS)

f2c:
	$(CC) -o f2c f2c.c $(CFLAGS)
gas:
	$(CC) -o gas gas.c $(CFLAGS)
inc: 
	$(CC) -o inc inc.c $(CFLAGS)

kg2lb:
	$(CC) -o kg2lb kg2lb.c $(CFLAGS)

lb2kg:
	$(CC) -o lb2kg lb2kg.c $(CFLAGS)

messages:
	$(CC) -o messages messages.c $(CFLAGS)

odo:
	$(CC) -o odo odo.c $(CFLAGS)

roundtime:
	$(CC) -o roundtime roundtime.c $(CFLAGS)

sr:
	$(CC) -o sr sr.c $(CFLAGS)

watermark:
	$(CC) -o watermark watermark.c $(CFLAGS)

install: all
	install -D -m 755 -o root -g root $(APPNAME) $(DESTDIR)$(PREFIX)/$(APPNAME)

clean:
	rm -rf *.o
