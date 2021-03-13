//
// Created by Kirill on 3/13/2021.
//

#include <iostream>
#include "TextIterator.h"

TTextIterator::TTextIterator(TTextNode *_node) {
    this->node = _node;
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

TTextNode *TTextIterator::get() {
    return this->node;
}

TTextIterator &TTextIterator::go_next_char() {
    if(this->node->is_letter()){

    }
}
