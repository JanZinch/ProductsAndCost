#include "Money.h"

Money::Money() = default;

Money::Money(float count, const char *currency) {

    this->_count = count;
    strcpy_s(this->_currency, currency);
}

Money::Money(const Money &object) {

    _count = object._count;
    strcpy_s(_currency, object._currency);
}

ostream& operator<<(ostream& out, const Money &object) {

    out << setiosflags(ios::fixed) << setprecision(2) << object._count << " " << object._currency;
    return out;
}

istream& operator>>(istream& in, Money &object) {

    in >> object._count >> object._currency;
    return in;
}

Money& Money::operator=(const Money &object)
{
    _count = object._count;
    strcpy_s(_currency, object._currency);

    return *this;
}

Money Money::operator+(const Money &object) {

    if (strcmp(this->_currency, object._currency) == 0) {

        float sum = this->_count + object._count;
        Money result(sum, _currency);
        return result;
    }
    else {
        
        return Default;
    }
}

Money Money::operator-(const Money &object) {

    if (strcmp(this->_currency, object._currency) == 0) {

        float sum = this->_count - object._count;
        Money Result(sum, _currency);
        return Result;

    }
    else {
        
        return Default;
    }

}

bool operator==(const Money &object_1, const Money &object_2) {

    if (strcmp(object_1._currency, object_2._currency) == 0) {

        if (object_1._count == object_2._count) {

            return true;
        }
        else {

            return false;
        }
    }
    else {

        return false;
    }

}

template<typename T>
Money Money::operator*(T &mult){
    
    return Money(_count * (float)mult, this->_currency);
}
