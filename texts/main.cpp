#include <iostream>
#include "TextNode.h"
int main()
{
    char* s = "hello word www dddd ddd\nbye bye";
    TTextNode* node = TTextNode::parse(s, NodeLevel::TEXT);
    std::cout<< static_cast<int>(node->get_level())<<std::endl;
    std::cout<<*node<<std::endl;
    return 0;
}
