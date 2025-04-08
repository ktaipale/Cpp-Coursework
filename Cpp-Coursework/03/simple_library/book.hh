#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <string>

class Book
{
public:
    Book(const std::string author, const std::string book_name);
    void loan(const Date& date);
    void date_advance(Date& date);
    void print();
    void renew();
    void give_back();
private:
    std::string author_;
    std::string book_name_;
    Date loan_day_;
    Date return_day_;
    bool is_loaned_ = false;
};

#endif // BOOK_HH
