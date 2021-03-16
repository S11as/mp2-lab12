//
// Created by Kirill on 3/13/2021.
//

#include <iostream>
#include "TextIterator.h"

TTextIterator::TTextIterator(TTextNode *_node) {
    this->node = _node;
}


TTextIterator::TTextIterator(const TTextIterator &_iter) {
    this->node = _iter.node;
    this->stack = _iter.stack;
}

TTextIterator &TTextIterator::go_next() {
    if(this->node->is_letter() && this->node->has_next()){
        this->node = this->node->get_next();
    } else if (this->node->is_letter()) {
        // буква у которой нет следующего элемента
        bool end_of_text = true;
        while(!this->stack.is_empty()){
            this->node = this->stack.pop();
            if(this->node->has_next()){
                end_of_text = false;
                this->node = this->node->get_next();
                break;
            }
        }
        if(end_of_text){
            // операция перехода на следующий элемент не выполнилась ни разу, значит мы в самом конце
            this->node = nullptr;
        }
    }else{
        // не буква - значит уровень выше 0, кладем элемент и опускаемся вниз
        this->stack.push(this->node);
        this->node = this->node->get_down();
    }
    return *this;
}

TTextIterator &TTextIterator::go_next(NodeLevel level) {
    this->go_next();
    while(this->node != nullptr){
        if(this->node->get_level() == level)
            break;
        this->go_next();
    }
    return *this;
}

TTextIterator &TTextIterator::go_next_char() {
    return this->go_next(NodeLevel::LETTER);
}

TTextIterator &TTextIterator::reset_to(NodeLevel level) {
    if(this->node!= nullptr){
        int current_lvl = static_cast<int>(this->node->get_level());
        int needed_lvl = static_cast<int>(level);
        if(current_lvl < needed_lvl){
            while(current_lvl<needed_lvl){
                if(!this->stack.is_empty()){
                    this->node = this->stack.pop();
                }else{
                    this->node = nullptr;
                }
                current_lvl++;
            }
        }else if(current_lvl > needed_lvl){
            while(current_lvl>needed_lvl){
                this->stack.push(this->node);
                this->node = this->node->get_down();
                current_lvl--;
            }
        }
    }
    return *this;
}

TTextIterator &TTextIterator::reset() {
    while(!this->stack.is_empty()){
        this->stack.pop();
    }
    this->node = nullptr;
    return *this;
}

TTextNode *TTextIterator::get() {
    return this->node;
}

int TTextIterator::get_str_len(int count) {
    int len = 0;
    int counted = 0;
    TStack<TSeparator> separators;
    while(this->node && counted<count){
        while(!this->node->is_letter()){
            separators.push(this->node->get_separator());
            this->go_next();
        }
        while(!separators.is_empty()){
            TSeparator s = separators.pop();
            len += s.get_len();
        }
        while(this->node && this->node->is_letter()){
            this->go_next();
            counted++;
            len++;
        }
    }
    return len;
}

