
all: linux win32

linux:
	$(MAKE) -f Makefile.linux

win32:
	$(MAKE) -f Makefile.win32

clean:
	$(MAKE) -f Makefile.linux clean
	$(MAKE) -f Makefile.win32 clean

