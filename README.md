NAME
====
libunicode -- The library provides the mutual conversion of Unicode encoding and UTF-8 coding.

INSTALL
=======

```bash
$ git clone git@github.com:perfgao/libunicode.git
$ cd libunicode
$ make
$ make install
```
The *libunicode.h* will be copied to the */usr/local/include/* directory and 
the *libunicode.a* will be copied to the */usr/local/lib/* directory.

Synopsis
========
```
#include<stdio.h>
#include"libunicode.h"

// encode: UTF-8 to unicode
void test_encode()
{
    char *teststr = "汉字 English 漢字 hрусский  текст بالعربية";

    int get_len = get_encoded_len(teststr);

    char *buffer = malloc(get_len);
    if (!buffer) {
        printf("malloc failed!");
        return;
    }

    encode(teststr, buffer);

    printf("encode: %s ->\n", teststr);
    printf("\t%s\n", buffer);

    free(buffer);
}

// decode: unicode to UTF-8
void test_decode()
{
    char *teststr3 = "s\\u0065l\\u0065ct * fr%u006fm table where id='1'";
    int get_len = get_decode_len(teststr3, 0);
    char *buffer = malloc(get_len);
    if (!buffer) {
        printf("malloc failed!");
        return;
    }

    decode(teststr3, buffer);

    printf("decode: %s ->\n\t%s\n", teststr3, buffer);

    char *teststr4 = "\\u6c49\\u5b57\\u6f22\\u5b57\\u0045\\u006e\\u0067\\u006c" \
                     "%u0069%u0073%u0068%u0440%u0443%u0441%u0441%u043a" \
                     "\\u0438\\u0439\\u0020\\u0020\\u0442\\u0435\\u043a\\u0441" \
                     "\\u0442\\u0628\\u0627\\u0644\\u0639\\u0631\\u0628\\u064a" \
                     "\\u0629";
    get_len = get_decode_len(teststr4, 0);
    buffer = malloc(get_len);
    if (!buffer) {
        printf("malloc failed!");
        return;
    }

    decode(teststr4, buffer);

    printf("decode: %s ->\n\t%s\n", teststr4, buffer);
}

int main ()
{
    test_encode();

    printf("===================\n");

    test_decode();

    return 0;
}
```

```
encode: 汉字 English 漢字 hрусский  текст بالعربية ->
	\u6c49\u5b57\u0020\u0045\u006e\u0067\u006c\u0069\u0073\u0068\u0020\u6f22\u5b57\u0020\u0068\u0440\u0443\u0441\u0441\u043a\u0438\u0439\u0020\u0020\u0442\u0435\u043a\u0441\u0442\u0020\u0628\u0627\u0644\u0639\u0631\u0628\u064a\u0629
===================
decode: s\u0065l\u0065ct * fr%u006fm table where id='1' ->
	select * from table where id='1'
decode: \u6c49\u5b57\u6f22\u5b57\u0045\u006e\u0067\u006c%u0069%u0073%u0068%u0440%u0443%u0441%u0441%u043a\u0438\u0439\u0020\u0020\u0442\u0435\u043a\u0441\u0442\u0628\u0627\u0644\u0639\u0631\u0628\u064a\u0629 ->
	汉字漢字Englishрусский  текстبالعربية
```