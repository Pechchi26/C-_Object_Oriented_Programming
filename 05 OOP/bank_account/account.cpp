#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), balance_(0),credit_limit_(0), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

/*void Account::generate_iban()
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
}*/

void Account::print() const
{
    std::cout  << owner_ <<" : "<< iban_
               <<" : "<< balance_ << " euros" << std::endl;

}

void Account::save_money(int amount)
{

        balance_+=amount;

}

void Account::set_credit_limit(int limit)
{
   if(has_credit_){
       credit_limit_=limit;

   }
   else{
       std::cout<<"Cannot set credit limit: the account has no credit card"<<std::endl;
   }
}

void Account::take_money(int amount)
{
    if (amount<=0)
    {
        std::cout<<"Cannot take money: balance underflow"<<std::endl;
        return;
    }
    int avilable_balance_=balance_;
    if(has_credit_){
        avilable_balance_ += credit_limit_;
    }
    if(amount<=avilable_balance_){
        balance_-=amount;
        std::cout<<amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;

    }
    else if(has_credit_){
        std::cout<<"Cannot take money: balance underflow"<<std::endl;
    }
    else{
         std::cout<<"Cannot take money: credit limit underflow"<<std::endl;
    }
}


void Account::transfer_to(Account& to, int amount)
{
    int available_balance = balance_;
    if (has_credit_) {
           available_balance += credit_limit_;
        }
    if (amount > 0 && amount <= available_balance) {
    take_money(amount);
    to.save_money(amount);

    }
    else{
        std::cout << "Cannot take money: balance underflow" << std::endl;
    }
}

// Setting initial value for the static attribute running_number_


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
