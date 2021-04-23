//
// Created by Kirill on 3/13/2021.
//

#ifndef TEXTSLIB_TTEXTFACTORY_H
#define TEXTSLIB_TTEXTFACTORY_H

#include "TextNode.h"
#include "Text.h"

class TTextFactory {
public:
    static TTextNode* create_node(char* s, NodeLevel level, int start=0, int end=0);
    static TTextNode* create_node(string s, NodeLevel level, int start=0, int end=0);
    static TText* create(char* s);
};


#endif //TEXTSLIB_TTEXTFACTORY_H
