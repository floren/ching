#	@(#)Makefile	8.1 (Berkeley) 05/31/93
DESTDIR=/usr/local/games/
DESTSHARE=/usr/local/share/games/ching/
DESTMAN=/usr/local/man/man6/

all:	ching.phx ching.cno

ching.phx:
	$(CC) -I. phx/ching.phx.c -o ching.phx

ching.cno:
	$(CC) -I. cno/ching.cno.c -o ching.cno

clean:
	rm ching.phx ching.cno

install:
	install -d ${DESTDIR} ${DESTSHARE} ${DESTMAN}
	install ching.sh ${DESTDIR}/ching
	install ching.phx ${DESTDIR}
	install ching.cno ${DESTDIR}
	install -m 444 hexagrams macros ${DESTSHARE}
	install -m 444 ching.6 ${DESTMAN}
