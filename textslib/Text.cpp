//
// Created by Kirill on 3/13/2021.
//

#include "Text.h"

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
