#include <iostream>
#include <Text.h>
#include <cstring>
#include "TextNode.h"
#include "TTextFactory.h"

int main() {
    char *s = "hello\nword\nwww dddddd\paqqqq";
    TText *node = TTextFactory::create(s);
    TTextIterator i = node->begin();
    node->_delete(5, i);
    std::cout << *(node)<<std::endl;
    TTextIterator j = node->find(NodeLevel::WORD, "www");
    char *ss = node->copy(12, j);
    int len = strlen(ss);
    for (int k = 0; k < len; ++k) {
        std::cout<<ss[k];
    }
//    TTextIterator b = node->begin();
//    b.reset_to(NodeLevel::PARAGRAPH);
//    while(b.get()){
//        std::cout<<static_cast<int>(b.get()->get_level())<<std::endl;
//        b.go_next(NodeLevel::PARAGRAPH);
//    }
    return 0;
}
