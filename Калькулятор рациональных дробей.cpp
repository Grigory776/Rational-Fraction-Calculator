#include <iostream>
#include<fstream>
#include <sstream>
#include<set>
#include<map>
#include<vector>
#include<stdexcept>
using namespace std;

int NOD(int a, int b) {

    while ((a > 0) && (b > 0))
    {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}

int NOK(int a, int b) {
    return a * b / NOD(a, b);
}


class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    void sokr(int& a, int& b) {
        if ((a == 0) || (b == 0)) { // определение знака
            a = 0;
            b = 1;
        }
        else {
            int tmp = a;
            int tmp1 = b;
            a = abs(tmp) / NOD(abs(tmp), abs(tmp1));
            b = abs(tmp1) / NOD(abs(tmp), abs(tmp1));
            if (((tmp < 0) && (tmp1 > 0)) || ((tmp > 0) && (tmp1 < 0))) {
                a = -a;
            }
        }

    }

    Rational(int numerator, int denominator) {

        if (denominator <= 0) throw invalid_argument("Invalid argument");
        sokr(numerator, denominator);
        p = numerator;
        q = denominator;

    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

    bool operator==(const Rational& b) const {
        if ((p == b.p) && (q == b.q))
            return true;
        return false;
    }
    Rational& operator+(const Rational& b) {

        int n = NOK(q, b.q);
        p = p * (n / q) + b.p * (n / b.q);
        q = n;
        sokr(p, q);
        return *this;
    }

    Rational& operator-(const Rational& b) {
        int n = NOK(q, b.q);
        p = p * (n / q) - b.p * (n / b.q);
        q = n;
        sokr(p, q);
        return *this;
    }
    Rational& operator*(const Rational& b) {
        p = p * b.p;
        q = q * b.q;
        sokr(p, q);
        return *this;
    }
    Rational& operator/(const Rational& b) {
        p = p * b.q;
        q = q * b.p;
        if (q == 0) throw  invalid_argument("Division by zero");
        sokr(p, q);
        return *this;
    }

    friend istream& operator>>(istream& in, Rational& R)
    {

        int t1 = R.p;
        int t2 = R.q;
        if (in) {
            in >> t1;
            in.ignore(1);
            in >> t2;
        }
        R = Rational(t1, t2);

        return in;
    }
    friend ostream& operator<<(ostream& out, const Rational& R)
    {
        out << R.p << "/" << R.q;
        return out;
    }

    friend bool operator<(const Rational& a, const Rational& b) {
        int zn = a.q;
        int i1 = a.p;
        int i2 = b.p;
        if (a.q != b.q) {
            zn = NOK(a.q, b.q);
            i1 = a.p * (zn / a.q);
            i2 = b.p * (zn / b.q);
        }
        if (i1 < i2) {
            return true;
        }
        else return false;


    }

private:
    int p;
    int q;
};





int main() {

    try {
        Rational a, b;
        char command;
        cin >> a >> command >> b;
        if (command == '+')
            cout << a + b;
        else if (command == '-')
            cout << a - b;
        else if (command == '*')
            cout << a * b;
        else
            cout << a / b;

    }
    catch (invalid_argument& ex) {
        cout << ex.what();
    }


    return 0;
}
