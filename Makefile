SUBDIRS= src

all:
	(cd src; ${MAKE} all)

install:
	(cd src; ${MAKE} install)

clean:
	@(cd src; ${MAKE} clean)

.PHONY: all clean install
