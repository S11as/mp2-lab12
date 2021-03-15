//
// Created by Kirill on 3/12/2021.
//

#include <cstring>
#include <iostream>
#include "TextNode.h"

TTextNode *TTextNode::get_next() const {
    return next;
}

void TTextNode::set_next(TTextNode *next) {
    TTextNode::next = next;
}

TTextNode *TTextNode::get_down() const {
    return down;
}

void TTextNode::set_down(TTextNode *down) {
    TTextNode::down = down;
}

char TTextNode::get_c() const {
    return c;
}

void TTextNode::set_c(char c) {
    TTextNode::c = c;
}

NodeLevel TTextNode::get_level() const {
    return level;
}

void TTextNode::set_level(NodeLevel level) {
    TTextNode::level = level;
}

TTextNode::TTextNode(char _c) {
    this->next = nullptr;
    this->down = nullptr;
    this->c = _c;
    this->level = NodeLevel::LETTER;
}


std::ostream &operator<<(std::ostream &ostream, const TTextNode &node) {
    TTextNode* current = new TTextNode(node);
    std::string separator;
    TStack<TTextNode*>stack{};
    TStack<std::string> separators;
    bool end_of_print = false;
    while(!end_of_print){
        while(!current->is_letter()){
            stack.push(current);
            switch (current->get_level()){
                case NodeLevel::LETTER:
                    separator = "";
                    break;
                case NodeLevel::WORD:
                    separator = " ";
                    break;
                case NodeLevel::STRING:
                    separator = "\n";
                    break;
                case NodeLevel::PARAGRAPH:
                    separator = "\\pa";
                    break;
                case NodeLevel::PAGE:
                    separator = "\\pb";
                    break;
            }
            separators.push(separator);
            current = current->get_down();
        }
        // letter
        while(current != nullptr){
            ostream<<current->get_c();
            current= current->get_next();
        }
        while(true){
            if(!stack.is_empty()){
                current = stack.pop()->get_next();
                std::string s = separators.pop();
                if(current != nullptr){
                    ostream<<s;
                    // есть следующий обьект, обрабатываем его
                    break;
                }else if(current == nullptr && !stack.is_empty()){
                    // дошли до последнего слова(строки) и надо подниматься еще выше
                    continue;
                }else{
                    end_of_print = true;
                    break;
                }
            }else{
                end_of_print = true;
                break;
            }
        }
    }
    return ostream;
}

bool TTextNode::is_letter() const {
    return this->level == NodeLevel::LETTER;
}

TTextNode::TTextNode(const TTextNode &node) {
    next = node.get_next();
    down = node.get_down();
    c = node.c;
    level = node.level;
}

bool TTextNode::has_next() const {
    return this->next != nullptr;
}

bool TTextNode::operator==(char c) {
    if(this->level != NodeLevel::LETTER)
        return false;
    else{
        return this->c == c;
    }
}

bool TTextNode::operator==(TTextNode& node) {
    if(this->level != node.get_level())
        return false;
    if(this->level == NodeLevel::LETTER){
        return this->c == node.get_c();
    }
    TTextNode* this_root = this->get_down();
    TTextNode* outer_root = node.get_down();
    if(*(outer_root) != *(this_root)){
        return false;
    }
    while(this_root->has_next() && outer_root->has_next()){
        this_root = this_root->get_next();
        outer_root = outer_root->get_next();
        if(*(outer_root) != *(this_root)){
            return false;
        }
    }
    if(this_root->has_next() || outer_root->has_next()){
        // разной длины но одно полностью включено в другое
        return false;
    }
    return true;
}

bool TTextNode::operator!=(TTextNode &node) {
    return !this->operator==(node);
}

bool TTextNode::has_down() const {
    return this->down == nullptr;
}
