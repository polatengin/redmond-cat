CC      := cc
CFLAGS  := -std=c11 -O2 -Wall -Wextra
PREFIX  := /usr/local
BINDIR  := $(PREFIX)/bin
MANDIR  := $(PREFIX)/share/man/man1
TARGET  := redmond-cat
SRC     := main.c
MANPAGE := redmond-cat.1

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

install: $(TARGET) $(MANPAGE)
	mkdir -p $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/$(TARGET)
	mkdir -p $(MANDIR)
	install -m 644 $(MANPAGE) $(MANDIR)/$(MANPAGE)

uninstall:
	rm -f $(BINDIR)/$(TARGET)
	rm -f $(MANDIR)/$(MANPAGE)

clean:
	rm -f $(TARGET)

.PHONY: all install uninstall clean
