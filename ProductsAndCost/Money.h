#pragma once
#include <iomanip>

using namespace std;

#define EMPTY_VALUE (-1.0f)

class Money
{
private:

    float count_;
    char currency_[6];
    //static Money error_;

public:

    Money();
    Money(float, const char*);
    Money(const Money&);
    friend ostream& operator<<(ostream&, const Money&);
    friend istream& operator>>(istream&, Money&);
    Money& operator=(const Money&);
    Money operator+(const Money&);
    Money operator-(const Money&);
    friend bool operator==(const Money&, const Money&);
    template<typename T>
    Money operator*(T&);
    float get();
    
};
