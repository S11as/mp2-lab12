//
// Created by Kirill on 3/13/2021.
//

#include <iostream>
#include <cstring>
#include "TTextFactory.h"

TTextNode *TTextFactory::create_node(char *s, NodeLevel level, int start, int end) {
    if(level== NodeLevel::LETTER){
        return new TTextNode(s[start]);
    }
    TSeparator* separator = new TSeparator("\n");
    bool no_separator = level == NodeLevel::WORD;
    if(no_separator){
        // чтобы пробел последний не попал как буква
        end--;
    }
    if (end == 0) {
        end = strlen(s);
    }
    // separators by node level higher than word
    switch (level){
        case NodeLevel::TEXT:{
            separator->set_s("\n");
            break;
        }
        case NodeLevel::STRING:{
            separator->set_s(" ");
        }
    }
    int local_start = start;
    TTextNode *root = nullptr;
    TTextNode *current = nullptr;
    TTextNode *next = nullptr;
    std::cout<<start<<" "<<end<<std::endl;
    for (int i = start; i <= end; ++i) {
        if (no_separator  || separator->in_begin(s,i,end) || i == end) {
            if (root == nullptr) {
                root = TTextFactory::create_node(s, static_cast<NodeLevel>(static_cast<int>(level) - 1), local_start, i);
                current = root;
            } else {
                next = TTextFactory::create_node(s, static_cast<NodeLevel>(static_cast<int>(level) - 1), local_start, i);
                current->set_next(next);
                current = next;
            }
            local_start = i + 1;
        }
    }
    TTextNode* wrapper = new TTextNode(0);
    wrapper->set_level(level);
    wrapper->set_down(root);
    return wrapper;
}

TText *TTextFactory::create(char *s) {
    return new TText(TTextFactory::create_node(s, NodeLevel::TEXT)->get_down());
}
