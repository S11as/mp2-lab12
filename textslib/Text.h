//
// Created by Kirill on 3/13/2021.
//

#ifndef TEXTSLIB_TEXT_H
#define TEXTSLIB_TEXT_H

#include "TextNode.h"
#include "TextIterator.h"
#include "Queue.h"

class TText {
public:
    TTextNode* root = nullptr;
public:
    explicit TText(TTextNode* r = nullptr);
    void set_root(TTextNode* r);
    TTextNode* get_root();
    ~TText();
    typedef TTextIterator iterator;
    iterator begin();
    iterator find(char c);
    iterator find(char* s);
    iterator find(NodeLevel level, char* s);
    iterator insert(char* s, iterator in);
    iterator _delete(int to_delete, iterator i);
    char* copy(int count, TTextIterator i);
public:
    static void renew_prevs(TTextIterator &i, TTextNode **&prevs);
    friend std::ostream &operator<<(std::ostream &ostream, const TText &text);

};


#endif //TEXTSLIB_TEXT_H
