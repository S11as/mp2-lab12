//
// Created by Kirill on 11/16/2020.
//

#ifndef POINTERLISTLIB_TLISTITERATOR_H
#define POINTERLISTLIB_TLISTITERATOR_H

#include "TListElem.h"
#include "iostream"
template <class T>
class TListIterator {
private:
    TListElem<T>* current;
public:

    T operator*(void);
    TListIterator<T>& operator++(int);
    TListIterator<T>& operator++();
    bool operator==(const TListIterator<T>& _iter);
    bool operator!=(const TListIterator<T>& _iter);

    explicit TListIterator(TListElem<T>* elem);
    TListIterator(TListIterator<T> const &iterator);
    ~TListIterator() = default;
};

template<class T>
T TListIterator<T>::operator*() {
    return this->current->GetData();
}

template<class T>
TListIterator<T>& TListIterator<T>::operator++(int) {
    this->current=this->current->GetNext();
    return *this;
}

template<class T>
TListIterator<T>& TListIterator<T>::operator++() {
    this->current=this->current->GetNext();
    return *this;
}

template<class T>
bool TListIterator<T>::operator==(const TListIterator<T> &_iter) {
    return this->current == _iter.current;
}
template<class T>
bool TListIterator<T>::operator!=(const TListIterator<T> &_iter) {
    return this->current != _iter.current;
}

template<class T>
TListIterator<T>::TListIterator(TListIterator<T> const& iterator) {
    this->current = new TListElem<T>(*iterator.current);
}

template<class T>
TListIterator<T>::TListIterator(TListElem<T> *elem) {
    this->current = elem;
}


#endif //POINTERLISTLIB_TLISTITERATOR_H
