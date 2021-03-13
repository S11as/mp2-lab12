//
// Created by Kirill on 3/13/2021.
//

#include "Separator.h"
#include "cstring"

TSeparator::TSeparator(char *s) {
    this->s = s;
    this->len = strlen(s);
}

bool TSeparator::is(const char *str, int start, int end) {
    for (int i = 0; i < this->len; ++i) {
        if(start+i>=end)
            return false;
        if(str[start+i]!=this->s[i])
            return false;
    }
    return true;
}

void TSeparator::set_s(char *s) {
    TSeparator::len=strlen(s);
    TSeparator::s = s;
}
