#include <iostream>
#include <Text.h>
#include "TextNode.h"
#include "TTextFactory.h"
int main()
{
    char* s = "hello word www dddd ddd\nbye bye";
    TText* node = TTextFactory::create(s);
    TText::iterator i = node->begin();
    while(i.get()){
        i.go_next();
    }

    return 0;
}
