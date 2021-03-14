//
// Created by Kirill on 3/12/2021.
//

#ifndef TEXTSLIB_TEXTNODE_H
#define TEXTSLIB_TEXTNODE_H
#include <fstream>
#include "Stack.h"
#include "Separator.h"

enum class NodeLevel {LETTER=0, WORD=1, STRING=2, TEXT=3};

class TTextNode {
protected:
    TTextNode* next;
    TTextNode* down;

protected:
    char c;
    NodeLevel level;
public:
    TTextNode *get_next() const;
    void set_next(TTextNode *next);
    TTextNode *get_down() const;
    void set_down(TTextNode *down);
    char get_c() const;
    void set_c(char c);
    NodeLevel get_level() const;
    void set_level(NodeLevel level);
    bool is_letter() const;
    bool has_next() const;
    bool contains(TTextNode* node);

    explicit TTextNode(char _c=0);
    TTextNode(NodeLevel _level=NodeLevel::LETTER, char* _s=0);
    TTextNode(const TTextNode &node);

    ~TTextNode();
    bool operator==(char c);
    bool operator==(TTextNode& node);
    bool operator!=(TTextNode& node);
    friend std::ostream &operator<<(std::ostream &ostream, const TTextNode &node);
};


#endif //TEXTSLIB_TEXTNODE_H
