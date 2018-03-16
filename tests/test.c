#include<stdio.h>
#include"libunicode.h"

// encode: UTF-8 to unicode
void test_encode()
{
    char *teststr = "abcd";

    int get_len = get_encoded_len(teststr);

    printf("src strlen: %d\n", strlen(teststr));
    printf("get encode len: %d\n", get_len);

    char *buffer = malloc(get_len);
    if (!buffer) {
        printf("malloc failed!");
        return;
    }

    encode(teststr, buffer);

    printf("buffer strlen: %d\n", strlen(buffer));
    printf("encode: %s -> %s\n", teststr, buffer);

    free(buffer);

    char *teststr1 = "汉字漢字Englishрусский  текстبالعربية";

    get_len = get_encoded_len(teststr1);

    buffer = malloc(get_len);
    if (!buffer) {
        printf("malloc failed!");
        return;
    }

    encode(teststr1, buffer);

    printf("encode: %s ->\n", teststr1);
    printf("%s\n", buffer);

    free(buffer);
}

// decode: unicode to UTF-8
void test_decode()
{
    char *teststr2 = "\\u0061";

    int get_len = get_decode_len(teststr2, 0);
    int get_len1 = get_decode_len(teststr2, 1);

    printf("get expected decode len: %d\n", get_len);
    printf("get accurate decode len: %d\n", get_len1);

    char *buffer = malloc(get_len1);
    if (!buffer) {
        printf("malloc failed!");
        return;
    }

    decode(teststr2, buffer);
 
    printf("decode: %s -> %s\n", teststr2, buffer);

    free(buffer);

    char *teststr3 = "s\\u0065l\\u0065ct * fr%u006fm table where id='1'";
    get_len = get_decode_len(teststr3, 0);
    buffer = malloc(get_len);
    if (!buffer) {
        printf("malloc failed!");
        return;
    }

    decode(teststr3, buffer);

    printf("decode: %s -> %s\n", teststr3, buffer);

    char *teststr4 = "\\u6c49\\u5b57\\u6f22\\u5b57\\u0045\\u006e\\u0067\\u006c" \
                     "\\u0069\\u0073\\u0068\\u0440\\u0443\\u0441\\u0441\\u043a" \
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

    printf("decode: %s -> %s\n", teststr4, buffer);
}

int main ()
{
    test_encode();

    printf("===================\n");

    test_decode();

    return 0;
}
