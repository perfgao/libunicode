SUBDIRS= src

all:
	(cd src; ${MAKE} all)

install:
	(cd src; ${MAKE} install)

test:
	(cd tests; ${MAKE} test)

clean:
	@(cd src; ${MAKE} clean)

.PHONY: all clean install
