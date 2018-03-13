#ifndef _LIBUNICODE_H
#define _LIBUNICODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_encoded_len(const char *src);
int encode(const char *src, char *dst);

int get_decode_len(const char *src, int opt);
int decode(const char *src, char *dst);

#endif
