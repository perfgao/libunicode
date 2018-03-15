
AR=ar -r

CC=cc
LD=ld
LDSHARED=ld -shared
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -g -O3 -fPIC

INSTALL=install
PREFIX=/usr/local
INSTALL_INCLUDE=${PREFIX}/include
INSTALL_LIB=${PREFIX}/lib

LIBNAME=unicode

STATICLIB_SUFFIX=a
STATICLIB=lib${LIBNAME}.${STATICLIB_SUFFIX}

SHAREDLIB_SUFFIX=so
SHAREDLIB=lib${LIBNAME}.${SHAREDLIB_SUFFIX}

HEADERS=libunicode.h

SOURCES=libunicode.c

OBJECTS=libunicode.o

all: ${STATICLIB} ${SHAREDLIB}

libunicode.o: libunicode.h
	${CC} ${CFLAGS} -c -o libunicode.o libunicode.c

${SHAREDLIB}: ${OBJECTS}
	${LD} -shared -o ${SHAREDLIB} ${OBJECTS} -lc

${STATICLIB}: ${OBJECTS}
	rm -f ${STATICLIB}
	${AR} ${STATICLIB} ${OBJECTS}

install: ${STATICLIB}
	${INSTALL} -d ${INSTALL_INCLUDE}
	${INSTALL} -c ${HEADERS} ${INSTALL_INCLUDE}
	${INSTALL} -d ${INSTALL_LIB}
	${INSTALL} -c ${STATICLIB} ${INSTALL_LIB}

.PHONY: install

clean:
	@rm -rf *.so *.a *.o
