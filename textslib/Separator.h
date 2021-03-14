//
// Created by Kirill on 3/13/2021.
//

#ifndef TEXTSLIB_SEPARATOR_H
#define TEXTSLIB_SEPARATOR_H


class TSeparator {
protected:
    char*s;

protected:
    int len;
public:
    explicit TSeparator(char*s= nullptr);
    bool in_begin(const char*str, int start, int end);
    void set_s(char *s);
};


#endif //TEXTSLIB_SEPARATOR_H
