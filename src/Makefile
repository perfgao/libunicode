
AR=ar -r

CC=cc
LD=ld
LDSHARED=ld -shared
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -g -O3 -fPIC

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

clean:
	@rm -rf *.so *.a *.o
