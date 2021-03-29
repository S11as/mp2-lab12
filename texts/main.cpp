#include <iostream>
#include <Text.h>
#include <cstring>
#include "TextNode.h"
#include "TTextFactory.h"

int main() {
    char *s = "hello world\nit is rainy today\pabye world";
    TText* text = TTextFactory::create(s);
    char *sequence = "itis";
    int len = strlen(sequence);
    TTextIterator i = text->find(sequence);
    for (int j = 0; j < len; ++j) {
        i.go_next_char();
    }
    return 0;
}
