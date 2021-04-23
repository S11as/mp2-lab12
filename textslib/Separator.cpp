//
// Created by Kirill on 3/13/2021.
//

#include "Separator.h"
#include "cstring"

TSeparator::TSeparator(char *s) {
    this->s = s;
    if(!s){
        this->len = 0;
    }else{
        this->len = strlen(s);
    }
}

bool TSeparator::in_begin(const char *str, int start, int end) {
    for (int i = 0; i < this->len; ++i) {
        if(start+i>=end)
            return false;
        if(str[start+i]!=this->s[i])
            return false;
    }
    return true;
}

bool TSeparator::in_begin(std::string str, int start, int end) {
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

std::ostream &operator<<(std::ostream &ostream, const TSeparator &separator) {
    for (int i = 0; i < separator.len; ++i) {
        ostream<<separator.s[i];
    }
    return ostream;
}

int TSeparator::get_len() {
    return this->len;
}

char *TSeparator::get_s() {
    return this->s;
}