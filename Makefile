SUBDIRS= src

all:
	(cd src; ${MAKE} all)

clean:
	@(cd src; ${MAKE} clean)

.PHONY: all clean
