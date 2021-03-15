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
    explicit TTextIterator(TTextNode* _node);
    TTextIterator(const TTextIterator& _iter);

    TTextIterator& go_next();
    TTextIterator& go_next(NodeLevel level);
    TTextIterator& go_next_char();
    TTextNode* get();
    TTextIterator& reset_to(NodeLevel level);
    TTextIterator& reset();
    TTextIterator& _delete(int count, TTextIterator i);
};


#endif //TEXTSLIB_TEXTITERATOR_H
