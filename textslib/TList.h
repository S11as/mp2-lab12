//
// Created by Kirill on 11/16/2020.
//

#ifndef POINTERLISTLIB_TLIST_H
#define POINTERLISTLIB_TLIST_H

#include <fstream>
#include "TListElem.h"
#include "TListIterator.h"
#include "iostream"
template <class T>
class TList
{
protected:
    TListElem<T>* root;
    TListElem<T>* last;
    int count;
public:
    TList();
    TList(TList<T>& _v);
    ~TList();

    TList<T>& operator =(TList<T>& _v);

    void InsFirst(T d);
    void InsLast(T d);
    void Ins(TListElem<T>* e, T d);

    bool IsEmpty(void) const;

    bool IsFull(void) const;

    int GetCount(void) const;

    TListElem<T>* GetFirst();
    TListElem<T>* GetLast();

    void DelFirst();
    void DelLast();
    void Del(TListElem<T>* e);

    TList<int>& multiplesToK(int k);

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TList<T1> &A);
    template <class T1>
    friend istream& operator>> (istream& istr, TList<T1> &A);

    static TList<T> &load(const char *name);
    void save(const char *name);

    typedef TListIterator<T> iterator;
    iterator begin(){
        return TListIterator<T> (this->root);
    };
    iterator end(){
        return TListIterator<T> (this->last->GetNext());
    };
};


template <class T1>
ostream& operator<< (ostream& ostr, const TList<T1> &A) {

    TListElem<T1>* i = A.root;

    while (i != 0)
    {
        ostr << *i << endl;
        i = i->GetNext();
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TList<T1> &A) {
    int count;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        T1 d;
        istr >> d;
        A.InsLast(d);
    }
    return istr;
}

template<class T>
inline TList<T>::TList()
{
    this->root = 0;
    this->last = 0;
    this->count = 0;
}

template <class T>
TList<T>::TList(TList<T>& _v)
{
    this->count = _v.count;

    TListElem<T>* iter = _v.root;
    if(iter !=0){
        auto* buffer = new TListElem<T>(*iter);
        buffer->SetPrev(0);
        buffer->SetNext(0);
        this->root = buffer;

        TListElem<T>* prev = buffer;
        iter = iter->GetNext();

        while(iter != 0){
            buffer = new TListElem<T>(*iter);

            buffer->SetNext(0);
            buffer->SetPrev(prev);
            prev->SetNext(buffer);

            prev = buffer;
            this->last = buffer;
            iter = iter->GetNext();
        }
    }
}
template <class T>
TList<T>::~TList()
{
    if(this->root != 0){
        TListElem<T>* prev = 0;
        while(this->root!=0){
            prev = this->root;
            this->root = this->root->GetNext();
            delete prev;
        }
    }
    this->root = 0;
    this->last = 0;
    this->count = 0;
}

template <class T>
TList<T>& TList<T>::operator =(TList<T>& _v)
{
    if(this == &_v)
        return *this;

    this->count = _v.count;

    if(this->root != 0){
        TListElem<T>* prev = 0;
        while(this->root!=0){
            prev = this->root;
            this->root = this->root->GetNext();
            delete prev;
        }
    }

    TListElem<T>* iter = _v.root;
    if(iter !=0){
        auto* buffer = new TListElem<T>(*iter);
        buffer->SetPrev(0);
        buffer->SetNext(0);
        this->root = buffer;

        TListElem<T>* prev = buffer;
        iter = iter->GetNext();

        while(iter != 0){
            buffer = new TListElem<T>(*iter);

            buffer->SetNext(0);
            buffer->SetPrev(prev);
            prev->SetNext(buffer);

            prev = buffer;
            this->last = buffer;
            iter = iter->GetNext();
        }
    }
    return *this;
}

template<class T>
inline void TList<T>::InsFirst(T d)
{
    TListElem<T>* elem = new TListElem<T>(d);
    elem->SetNext(this->root);
    if(this->root!=0)
        this->root->SetPrev(elem);
    elem->SetPrev(0);
    this->root = elem;
    this->count++;
    if(this->last==0)
        this->last=elem;
}

template<class T>
inline void TList<T>::InsLast(T d)
{
    auto* elem = new TListElem<T>(d);
    elem->SetNext(0);
    elem->SetPrev(this->last);
    if(this->last != 0)
        this->last->SetNext(elem);
    this->last = elem;
    this->count++;
    if(this->root==0)
        this->root=elem;
}

template<class T>
inline void TList<T>::Ins(TListElem<T>* e, T d)
{
    auto* elem = new TListElem<T>(d);
    elem->SetNext(e->GetNext());
    elem->SetPrev(e);
    e->GetNext()->SetPrev(elem);
    e->SetNext(e);
    count++;
}

template<class T>
inline bool TList<T>::IsEmpty(void) const
{
    return this->count == 0;
}

template<class T>
inline bool TList<T>::IsFull(void) const
{
    try
    {
        auto* tmp = new TListElem<T>(0);
        delete tmp;
        return false;
    }
    catch (...)
    {
        return true;
    }
}


template<class T>
inline TListElem<T>* TList<T>::GetFirst()
{
    return this->root;
}

template<class T>
inline TListElem<T>* TList<T>::GetLast()
{
    return this->last;
}

template<class T>
inline void TList<T>::DelFirst()
{
    auto* elem = this->root;
    this->root = this->root->GetNext();
    delete elem;
    this->count--;
}

template<class T>
inline void TList<T>::DelLast()
{
    auto* elem = this->last;
    this->last = this->last->GetPrev;
    delete elem;
    this->count--;
}

template<class T>
inline void TList<T>::Del(TListElem<T>* e)
{
    e->GetNext()->SetPrev(e->GetPrev());
    e->GetPrev()->SetNext(e->GetNext());
    count--;
    delete e;
}

template<class T>
inline int TList<T>::GetCount() const
{
    return this->count;
}

template<class T>
TList<T> &TList<T>::load(const char *name) {
    std::ifstream file;
    file.open(name, std::fstream::in);
    if (!file.is_open())
        throw "Cant open such file";
    int size;
    file >> size;
    auto* list = new TList();
    file>>*list;
    file.close();
    return *list;
}

template<class T>
void TList<T>::save(const char *name) {
    fstream file;
    file.open(name, fstream::out);
    if (!file.is_open())
        throw "Cant open such file";
    file << this->count << "\n" << *this;
    file.close();
}

template<class T>
TList<int>& TList<T>::multiplesToK(int k) {
    auto* c = new TList();
    iterator i = this->begin();
    while (this->end()!=i){
        if(*i % k == 0){
            c->InsLast(*i);
        }
        i++;
    }
    return *c;
}


#endif //POINTERLISTLIB_TLIST_H
