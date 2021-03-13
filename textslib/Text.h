//
// Created by Kirill on 3/13/2021.
//

#ifndef TEXTSLIB_TEXT_H
#define TEXTSLIB_TEXT_H

#include "TextNode.h"
#include "TextIterator.h"
class TText {
protected:
    TTextNode* root = nullptr;
public:
    explicit TText(TTextNode* r = nullptr);
    void set_root(TTextNode* r);
    TTextNode* get_root();
    typedef TTextIterator iterator;
    iterator begin();
};


#endif //TEXTSLIB_TEXT_H
