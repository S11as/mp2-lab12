#include <iostream>
#include <Text.h>
#include <cstring>
#include "TextNode.h"
#include "TTextFactory.h"

int main() {
    char *s = "hello world\nit is rainy today\\pabye world";
    TText* text = TTextFactory::create(s);
    char *sequence = "world";
    int len = strlen(sequence);
    TTextIterator i = text->begin();
    text->_delete(28,i);
    i.go_next_char();
    for (int j = 0; j < len; ++j) {
        std::cout<<i.get()->get_c()<<" "<<sequence[j]<<std::endl;
        i.go_next_char();
    }
    return 0;
}
