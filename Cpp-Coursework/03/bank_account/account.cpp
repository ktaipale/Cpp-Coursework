#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit) {
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << saldo << " euros" << std::endl;
}

void Account::set_credit_limit(int luotto) {
    if (Account::has_credit_ == false){
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
    else {
        velkasaldo += luotto;
    }
}

void Account::transfer_to(Account& maksunsaaja, int maara){
    if (saldo >= maara){
        maksunsaaja.saldo += maara;
        saldo -= maara;
        std::cout << maara << " euros taken: new balance of " << iban_ << " is " << saldo << " euros" << std::endl;
    } else if (saldo + velkasaldo >= maara) {
        int siirtomaara = 0;
        siirtomaara = maara;
        maara -= saldo;
        saldo -= siirtomaara;
        maksunsaaja.saldo += siirtomaara;
        std::cout << siirtomaara << " euros taken: new balance of " << iban_ << " is " << saldo << " euros" << std::endl;
    }else if (saldo + velkasaldo <= maara) {
        std::cout << "Cannot take money: credit limit overflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    } else {
        std::cout << "Cannot take money: balance underflow" << std::endl;
        std::cout << saldo << " + " << velkasaldo << "Transfer from " << iban_ << " failed" << std::endl;
    }
}

void Account::save_money(int talletus) {
    saldo += talletus;
}

void Account::take_money(int nosto) {
    if (saldo >= nosto) {
        saldo -= nosto;
        std::cout << nosto << " euros taken: new balance of " << iban_ << " is " << saldo << " euros" << std::endl;
    } else if(saldo + velkasaldo >= nosto and has_credit_ == true) {
        int nostomaara = 0;
        nostomaara = nosto;
        nosto -= saldo;
        saldo -= nostomaara;
        std::cout << nostomaara << " euros taken: new balance of " << iban_ << " is " << saldo << " euros" << std::endl;
    } else if (saldo + velkasaldo < nosto and has_credit_ == true) {
        std::cout << "Cannot take money: credit limit overflow" << std::endl;
    } else {
        std::cout << "Cannot take money: balance underflow" << std::endl;
    }
}
