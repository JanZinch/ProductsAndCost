#include "Money.h"

//Money Money::error_ = Money(0.0f, "ERROR");

Money::Money() {

    count_ = EMPTY_VALUE;
    strcpy_s(currency_, "N/D");
}

Money::Money(float count, const char *currency) {

    this->count_ = count;
    strcpy_s(this->currency_, currency);

}

Money::Money(const Money &object) {

    count_ = object.count_;
    strcpy_s(currency_, object.currency_);

}

ostream& operator<<(ostream& out, const Money &object) {

    out << setiosflags(ios::fixed) << setprecision(2) << object.count_ << " " << object.currency_;
    return out;
}

istream& operator>>(istream& in, Money &object) {

    in >> object.count_ >> object.currency_;
    return in;
}

Money& Money::operator=(const Money &object)
{
    count_ = object.count_;
    strcpy_s(currency_, object.currency_);

    return *this;
}

Money Money::operator+(const Money &object) {

    if (strcmp(this->currency_, object.currency_) == 0) {

        float sum = this->count_ + object.count_;
        Money result(sum, currency_);
        return result;
    }
    else {
        
        return Money(0, "ERROR");
    }
}

Money Money::operator-(const Money &object) {

    if (strcmp(this->currency_, object.currency_) == 0) {

        float sum = this->count_ - object.count_;
        Money Result(sum, currency_);
        return Result;

    }
    else {
        
        return Money(0, "ERROR");
    }

}

bool operator==(const Money &object_1, const Money &object_2) {

    if (strcmp(object_1.currency_, object_2.currency_) == 0) {

        if (object_1.count_ == object_2.count_) {

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

    Money result(count_ * (float)mult, this->currency_);
    return result;
}

float Money::get() {

    return count_;
}