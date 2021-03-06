//
// Created by Kirill on 3/12/2021.
//

#ifndef TEXTSLIB_TEXTNODE_H
#define TEXTSLIB_TEXTNODE_H
#include <fstream>
#include "Stack.h"
#include "Separator.h"
#include "TList.h"
enum class NodeLevel {LETTER=0, WORD=1, STRING=2, PARAGRAPH=3, PAGE=4, TEXT=5};

class TTextNode {
protected:
    TTextNode* next;
    TTextNode* down;
    static TList<TTextNode*> text_nodes;
    static TTextNode* first_free;
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
    TSeparator get_separator();
    NodeLevel get_level() const;
    void set_level(NodeLevel level);
    bool is_letter() const;
    bool has_next() const;
    bool has_down() const;

    explicit TTextNode(char _c=0);
    TTextNode(const TTextNode &node);

    ~TTextNode() = default;
    bool operator==(char c);
    bool operator==(TTextNode& node);
    bool operator!=(TTextNode& node);
    friend std::ostream &operator<<(std::ostream &ostream, const TTextNode &node);

    static void init_mem(int size= 100);
    static void free_mem();
    void* operator new(size_t size);
    void operator delete(void* p);
};


#endif //TEXTSLIB_TEXTNODE_H
