#include "libunicode.h"
#include <stdio.h>


int get_encoded_len(const char *src)
{
    int         i;
    int         len;

    if (!src) {
        return -1;
    }
  
    i = 0;
    len = 0;
    while (src[i]) {
        if ((src[i] & 0xff) >= 0x00 && (src[i] & 0xff) <= 0x7f) {
            i++;
            len++;
        } else if (((src[i] & 0xff) & 0xe0) == 0xc0) {
            i += 2;
            len++;
        } else if (((src[i] & 0xff) & 0xf0) == 0xe0) {
            i += 3;
            len++;
        } else {
            return -1;
        }
    }

    return (len * 6 + 1); /* '%uXXXX' and '\0' */
}

int encode(const char *src, char *dst)
{
    int            n;
    int            i;
    char          *d;
    unsigned char  vh, vl, t1, t2, t3;

    if (!src || !dst) {
        return -1;
    }

    i = 0;
    d = dst;
    while (src[i]) {
        if ((src[i] & 0xff) >= 0x00 && (src[i] & 0xff) <= 0x7f) {
            vh = 0;
            vl = (unsigned char)(src[i++]);
        } else if (((src[i] & 0xff) & 0xe0) == 0xc0) {
            t1 = (unsigned char)(src[i++] & 0x1f);
            t2 = (unsigned char)(src[i++] & 0x3f);

            vl = (unsigned char)(((t1 & 0x03) << 6) | t2);
            vh = (unsigned char)(t1 >> 2);
        } else if (((src[i] & 0xff) & 0xf0) == 0xe0) {
            t1 = (unsigned char)(src[i++] & 0x0f);
            t2 = (unsigned char)(src[i++] & 0x3f);
            t3 = (unsigned char)(src[i++] & 0x3f);

            vl = (unsigned char)(((t2 & 0x03) << 6) | t3);
            vh = (unsigned char)((t2 >> 2) | (t1 << 4));
        } else {
            return -1;
        }
        
        n = sprintf(d, "\\u%02x%02x", vh, vl);
        d += n;
    }

    d[0] = '\0';

    return (d - dst);
}

int get_decode_len(const char *src, int opt)
{
    int   i, hex, len, srclen, sublen;
    char  temp[5];
    char *pos = NULL;

    if (!src) {
        return -1;
    }

    srclen = strlen(src);

    if (opt == 0) {
        return strlen(src) + 1;
    }
    
    i = 0;
    len = 0;
    while (src[i]) {
        if ((src[i+1] == 'u') && (src[i] == '\\' || src[i] == '%')) {
            sublen = (srclen - (i + 2)) >= 4 ? 4 : (srclen - (i + 2));

            memset(temp, 0, sizeof(temp));
            memcpy(temp, src + i + 2, sublen);

            hex = strtol(temp, &pos, 16);
            sublen = pos - &temp[0];

            if (hex == 0x00 && sublen == 0) {
                len += 2;
                i += 2;
            } else if (hex <= 0x007f) {
                len++;
                i += (2 + sublen);
            } else if (hex >= 0x0080 && hex <= 0x07ff) {
                len += 2;
                i += (2 + sublen);
            } else if (hex >= 0x0800 && hex <= 0xffff) {
                len += 3;
                i += (2 + sublen);
            }

        } else {
            len++;
            i++;
        }
    }

    if (len == 0) {
        return 0;
    }

    return len + 1;
}

int decode(const char *src, char *dst)
{
    int   i, hex, srclen, sublen;
    char  temp[5];
    char *d;
    char *pos = NULL;

    if (!src || !dst) {
        return -1;
    }
    
    i = 0;
    d = dst;
    srclen = strlen(src);
    while (src[i]) {
        if ((src[i+1] == 'u') && (src[i] == '\\' || src[i] == '%')) {
            sublen = (srclen - (i + 2)) >= 4 ? 4 : (srclen - (i + 2));

            memset(temp, 0, sizeof(temp));
            memcpy(temp, src + i + 2, sublen);

            hex = strtol(temp, &pos, 16);
            sublen = pos - &temp[0];

            if (hex == 0x00 && sublen == 0) {
                memcpy(d, &src[i], 2);
                d += 2;
                i += 2;
            } else if (hex <= 0x007f) {
                sprintf(d++, "%c", hex & 0x7f);
                i += (2 + sublen);
            } else if (hex >= 0x0080 && hex <= 0x07ff) {
                sprintf(d++, "%c", ((hex >> 6) & 0x1f ) | 0xc0);
                sprintf(d++, "%c", (hex & 0x3f ) | 0x80);
                i += (2 + sublen);
            } else if (hex >= 0x0800 && hex <= 0xffff) {
                sprintf(d++, "%c", ((hex >> 12) & 0x0f) | 0xe0);
                sprintf(d++, "%c", ((hex >> 6) & 0x3f) | 0x80);
                sprintf(d++, "%c", (hex & 0x3f) | 0x80);
                i += (2 + sublen);
            }

        } else {
            sprintf(d++, "%c", src[i]);
            i++;
        }
    }

    return (d - dst);
}
