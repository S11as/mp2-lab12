//
// Created by Kirill on 3/13/2021.
//

#include <cstring>
#include "Text.h"
#include "TTextFactory.h"

void TText::set_root(TTextNode *r) {
    this->root = r;
}

TText::TText(TTextNode *r) {
    this->root = r;
}

TTextNode *TText::get_root() {
    return this->root;
}

TText::iterator TText::begin() {
    return TText::iterator(this->root);
}

TText::iterator TText::find(char c) {
    TTextIterator iter = this->begin();
    while(iter.get()){
        if(*(iter.get()) == c)
            break;
        iter.go_next_char();
    }
    return iter;
}

TText::iterator TText::find(char *s) {
    TTextIterator iter = this->begin();
    bool not_found = true;
    int str_index = 0;
    int found_length = strlen(s);
    while(iter.get() && not_found){
        if(*(iter.get()) == s[str_index]){
            TTextIterator iter2 = iter;
            while(iter2.get()){
                if(*(iter2.get()) == s[str_index]){
                    str_index++;
                    iter2.go_next_char();
                    if(str_index == found_length){
                        not_found = false;
                        break;
                    }
                }else{
                    str_index = 0;
                    break;
                }
            }
        }else{
            str_index = 0;
            iter.go_next_char();
        }
    }
    if(not_found){
        iter.reset();
    }
    return iter;
}

TText::iterator TText::find(NodeLevel level, char *s) {
    switch(level){
        case NodeLevel::LETTER:{
            return this->find(s[0]);
        }
        case NodeLevel::WORD:{
            TTextNode* word = TTextFactory::create_node(s, NodeLevel::WORD);
            TTextIterator iter = this->begin();
            iter.reset_to(NodeLevel::WORD);
            while(iter.get()){
                if(*(iter.get()) == *(word)){
                    break;
                }
                iter.go_next(NodeLevel::WORD);
            }
            return iter;
        }
    }
    return TText::iterator(nullptr);
}
