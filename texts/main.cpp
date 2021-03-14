#include <iostream>
#include <Text.h>
#include "TextNode.h"
#include "TTextFactory.h"
int main()
{
    char* s = "hello word www dddd ddd\nbye bye";
    TText* node = TTextFactory::create(s);
    TTextIterator i = node->find("word");
    std::cout<<i.get()->get_c()<<std::endl;
    return 0;
}
