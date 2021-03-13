//
// Created by Kirill on 3/13/2021.
//

#ifndef TEXTSLIB_TEXTITERATOR_H
#define TEXTSLIB_TEXTITERATOR_H

#include "TextNode.h"
#include "Stack.h"

class TTextIterator {
protected:
    TTextNode* node;
    TStack<TTextNode*> stack = TStack<TTextNode *>();
public:
    TTextIterator(TTextNode* _node);
    TTextIterator& go_next();
    TTextIterator& go_next_char();
    TTextNode* get();
};


#endif //TEXTSLIB_TEXTITERATOR_H
