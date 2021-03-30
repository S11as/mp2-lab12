//
// Created by Kirill on 3/13/2021.
//

#ifndef TEXTSLIB_SEPARATOR_H
#define TEXTSLIB_SEPARATOR_H


#include <ostream>

class TSeparator {
protected:
    char*s;
    int len;
public:
    explicit TSeparator(char*s= nullptr);
    bool in_begin(const char*str, int start, int end);
    bool in_begin(std::string str, int start, int end);
    void set_s(char *s);
    char* get_s();
    int get_len();
    friend std::ostream &operator<<(std::ostream &ostream, const TSeparator &separator);
};


#endif //TEXTSLIB_SEPARATOR_H
