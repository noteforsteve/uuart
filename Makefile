CC=cl
CFLAGS=/Zi /Od /c /WX /W4 /DDEBUG /DWINDOWS /DUART_TESTS /D_CRT_SECURE_NO_WARNINGS

LINK=link
LFLAGS=/NOLOGO /DEBUG 

OBJS=common.obj\
	debug.obj\
	winuart.obj\
	uart.obj\
	portable.obj\
	main.obj\

all: uuart.exe

main.obj : main.h main.c
	$(CC) $(CFLAGS) main.c

debug.obj : debug.h debug.c
	$(CC) $(CFLAGS) debug.c

common.obj : common.h common.c
	$(CC) $(CFLAGS) common.c

winuart.obj : winuart.h winuart.c
	$(CC) $(CFLAGS) winuart.c

uart.obj : uart.h uart.c
	$(CC) $(CFLAGS) uart.c

portable.obj : portable.h portable.c
	$(CC) $(CFLAGS) portable.c

uuart.exe : $(OBJS)
    $(LINK) $(LFLAGS) $** /OUT:$@

clean:
    del *.exe *.obj *.ilk *.manifest *.pdb *.suo

