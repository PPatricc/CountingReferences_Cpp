#pragma once

#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
using namespace std;

class rcstring {
    struct rctext;
    rctext* data;

public:
    class Range {};
    rcstring();
    rcstring(const char*);
    rcstring(const rcstring&);
    ~rcstring();
    rcstring& operator=(const rcstring&);
    rcstring& operator+=(const rcstring&);
    rcstring operator+(const rcstring&) const;
    friend ostream& operator<<(ostream&, const rcstring&);
    void check(unsigned int i) const;
    char read(unsigned int i) const;
    void write(unsigned int i, char c);
    int test();

    char operator[](unsigned int i) const;
    char& operator[](unsigned int i);

    int atoi();
    rcstring& toLower();
    rcstring left(int n);
};

struct rcstring::rctext {
    char* s;
    unsigned int size;
    unsigned int n;

    rctext(unsigned int nsize, const char* p) {
        n = 1;
        size = nsize;
        s = new char[size + 1];
        strncpy(s, p, size);
        s[size] = '\0';
    };
    ~rctext() { delete[] s; };
    rctext* detach() {
        if (n == 1)
            return this;
        rctext* t = new rctext(size, s);
        n--;
        return t;
    };

private:
    rctext(const rctext&);
    rctext& operator=(const rctext&);
};

inline rcstring::rcstring() { data = new rctext(0, ""); }

inline rcstring::rcstring(const rcstring& x) {
    x.data->n++;
    data = x.data;
}
inline rcstring::~rcstring() {
    if (--data->n == 0)
        delete data;
}

rcstring& rcstring::operator=(const rcstring& x) {
    x.data->n++;
    if (--data->n == 0)
        delete data;
    data = x.data;
    return *this;
}

rcstring::rcstring(const char* s) { data = new rctext(strlen(s), s); }

ostream& operator<<(ostream& o, const rcstring& s) { return o << s.data->s; }

rcstring& rcstring::operator+=(const rcstring& s) {
    unsigned int newsize = data->size + s.data->size;
    rctext* newdata = new rctext(newsize, data->s);
    strcat(newdata->s, s.data->s);
    if (--data->n == 0)
        delete data;
    data = newdata;
    return *this;
}

rcstring rcstring::operator+(const rcstring& s) const {
    return rcstring(*this) += s;
}

inline void rcstring::check(unsigned int i) const {
    if (data->size <= i)
        throw Range();
}

inline char rcstring::read(unsigned int i) const { return data->s[i]; }

inline void rcstring::write(unsigned int i, char c) {
    data = data->detach();
    data->s[i] = c;
}

char rcstring::operator[](unsigned int i) const {
    cout << "char rcstring::operator[](unsigned int i) const" << endl;
    check(i);
    return data->s[i];
}

char& rcstring::operator[](unsigned int i) {
    cout << "char& rcstring::operator[](unsigned int i)" << endl;
    check(i);
    data = data->detach();
    return data->s[i];
}

int rcstring::atoi() {
    int tmp = 0;
    for (int i = 0; this->data->s[i]; ++i) {
        tmp = tmp * 10 + this->data->s[i] - '0';
    }
    return tmp;
}



rcstring& rcstring::toLower() {

    for(int i = 0 ; this->read(i) != '\0' ; i++)
    {
        if(this->read(i) >= 'A' && this->read(i) <= 'Z')
        {
            this->write(i,this->read(i) + 32);
        }
    }
    return *this;

}

rcstring rcstring::left(int n) {

    char *temp = (char *)malloc(n + 1);
    for(int i = 0 ; i < n ; i++)
    {
        *(temp + i) = this->read(i);
    }
    *(temp + n) = '\0';
    rcstring res(temp);
    free(temp);
    return res;
}

inline int rcstring::test(){
    return this->data->n;
}


