#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
//#include <cmath>
//#include <locale>
//#include <cctype>
#include <fstream>
//#include <iomanip>
#include <sstream>

int gcd(int a,int b){
    while ((a > 0) && (b > 0)) {
        if (a > b) {
            a %= b;
        }
        else {
            b %= a;
        }
    }
    return a + b;
}
 
class Rational {
public:
    Rational() {
        chisl = 0;
        znam = 1;
    }
 
    Rational(int numerator, int denominator) {
        if (denominator < 0) {
            if (numerator < 0) {
                denominator = abs(denominator);
                numerator = abs(numerator);
            }
            else {
                denominator = abs(denominator);
                numerator = -numerator;
            }
        }
        if (numerator == 0) {
            denominator = 1;
        }
        int nod = gcd(abs(numerator), abs(denominator));
        chisl = numerator / nod;
        znam = denominator / nod;
    }
 
    int Numerator() const {
        return chisl;
    }
 
    int Denominator() const {
        return znam;
    }
 
private:
    int chisl, znam;
 
};
bool operator == (const Rational& a, const Rational& b) {
    if ((a.Numerator() == b.Numerator()) && (a.Denominator() == b.Denominator())) {
        return true;
    }
    else {
        return false;
    }
}
Rational operator + (Rational a, Rational b) { //и тут перегрузим, и дальше тоже
    int num = (a.Numerator() * b.Denominator()) + (b.Numerator() * a.Denominator());
    int den = a.Denominator() * b.Denominator();
    return {num, den};
}
Rational operator - (Rational a, Rational b) {
    int num = (a.Numerator() * b.Denominator()) - (b.Numerator() * a.Denominator());
    int den = a.Denominator() * b.Denominator();
    return {num, den};
}
Rational operator * (Rational a, Rational b) {
    return {(a.Numerator()*b.Numerator()), (a.Denominator()*b.Denominator())};
}
Rational operator / (Rational a, Rational b) {
    return {(a.Numerator() * b.Denominator()), (a.Denominator() * b.Numerator())};
}
ostream& operator<<(ostream& stream, const Rational& a){
    stream << a.Numerator() << "/" << a.Denominator();
    return stream;
}
istream& operator >> (istream& stream, Rational& r) {
    int num, den;
    if (stream >> num && stream.ignore(1) && stream >> den) {
        r = {num, den};
    }
    return stream;
}
// чтобы сравнить lhs с rhs, сравним их разность с нулём, что равносильно сравнению с нулём числителя
bool operator < (const Rational& lhs, const Rational& rhs) {
  return (lhs - rhs).Numerator() < 0;
}
