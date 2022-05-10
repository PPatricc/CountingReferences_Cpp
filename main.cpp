#include "rcstring.h"

void Display(rcstring &a, rcstring &b,rcstring &c){
    cout << "a: " << a.test() << " b: " << b.test() << " c: " << c.test() << endl;
}

void test(rcstring &a, rcstring &b,rcstring &c){
    cout << "________________" << endl << "TEST 1" << endl;
    a= "Ala";
    b="ma";
    c="kota";
    Display(a,b,c); // Ala ma kota
    b=a;
    Display(a,b,c); // Ala Ala kota
    b=a+c;
    Display(a,b,c); //Ala Alakota kota
    cout <<"________________" << endl;
}

void testToLower(rcstring &a, rcstring &b,rcstring &c){
    cout << "TEST ToLower" << endl;
    a= "Ala";
    b="ma";
    c="Kota";
    Display(a,b,c); // Ala ma Kota

    b = a;
    Display(a,b,c); // Ala Ala Kota

    a.toLower();
    Display(a,b,c); // ala Ala Kota

    a = b = c;
    Display(a,b,c); // Ala Ala Ala

    a.toLower();
    Display(a,b,c); // ala Ala Ala

    b=a;
    Display(a,b,c); // ala ala Ala
    a.toLower();
    Display(a,b,c); // ala ala Ala

    cout <<"________________" << endl;
}

void testLeft(rcstring &a, rcstring &b, rcstring &c){
    cout << "Test Left" <<endl;
    a = "Ala ma kota";
    b=a;
    cout << "a = " << a << " | "<< " b = "<< b << endl;
    Display(a, b, c);
    a=a.left(3);
    cout << "a = " << a << " | "<< " b = "<< b << endl;
    Display(a,b,c);
    cout <<"________________" << endl;
}

void testGeneral(rcstring &a, rcstring &b,rcstring &c){
    test(a,b,c);
    testToLower(a,b,c);
    testLeft(a,b,c);
}

int main() {
    rcstring a,b,c;
    testGeneral(a,b,c);
    return 0;
}