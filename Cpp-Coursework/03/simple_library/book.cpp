#include "book.hh"
#include "date.hh"
#include <iostream>
#include <string>

Book::Book(const std::string author, const std::string book_name):
    author_(author), book_name_(book_name){
}
void Book::print() {
    std::cout << author_ << " : " << book_name_ << std::endl;
    if (is_loaned_ == true) {
        std::cout << "- loaned: "; loan_day_.print();
        std::cout << "- to be returned: "; return_day_.print();
    } else {
        std::cout << "- available" << std::endl;
    }
}
void Book::loan(const Date& date) {
    if (is_loaned_){
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }
    loan_day_ = date;
    return_day_ = loan_day_;
    return_day_.advance(28);
    is_loaned_ = true;
}

void Book::renew(){
    if (is_loaned_ == false) {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    } else {
        return_day_.advance(28);
    }
}
void Book::give_back(){
    is_loaned_ = false;
}
