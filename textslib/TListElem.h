//
// Created by Kirill on 11/16/2020.
//

#ifndef POINTERLISTLIB_TLISTELEM_H
#define POINTERLISTLIB_TLISTELEM_H


#include <iosfwd>

using namespace std;

template <class T>
class TListElem
{
protected:
    T data;
    TListElem* next;
    TListElem* prev;
public:
    TListElem(T _data);
    ~TListElem();

    T GetData();
    TListElem* GetNext();
    TListElem* GetPrev();

    void SetData(T _data);
    void SetNext(TListElem* _next);
    void SetPrev(TListElem* _prev);

    bool operator==(TListElem& _elem);
    bool operator!=(TListElem& _elem);


    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TListElem<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, TListElem<T1>& A);
};


template<class T1>
inline ostream& operator<<(ostream& ostr, const TListElem<T1>& A)
{
    ostr << A.data;
    return ostr;
}

template<class T1>
inline istream& operator>>(istream& istr, TListElem<T1>& A)
{
    istr >> A.data;
    return istr;
}


template<class T>
inline TListElem<T>::TListElem(T _data)
{
    data = _data;
    next = 0;
    prev = 0;
}

template<class T>
inline TListElem<T>::~TListElem()
{
    next = 0;
    prev = 0;
}

template<class T>
inline T TListElem<T>::GetData()
{
    return data;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetNext()
{
    return next;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetPrev()
{
    return prev;
}

template<class T>
inline void TListElem<T>::SetData(T _data)
{
    data = _data;
}

template<class T>
inline void TListElem<T>::SetNext(TListElem<T>* _next)
{
    next = _next;
}

template<class T>
inline void TListElem<T>::SetPrev(TListElem<T>* _prev)
{
    prev = _prev;
}

template<class T>
bool TListElem<T>::operator==(TListElem &_elem) {
    return this->GetData() == _elem.GetData();
}

template<class T>
bool TListElem<T>::operator!=(TListElem &_elem) {
    return this->GetData() != _elem.GetData();
}


#endif //POINTERLISTLIB_TLISTELEM_H
