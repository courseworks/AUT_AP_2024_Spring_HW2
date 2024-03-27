#ifndef BANK_H // Prevents double inclusion of this header
#define BANK_H

#include <compare>  // For std::strong_ordering
#include <map>      // For std::map
#include <optional> // For std::optional
#include <string>   // For std::string
#include <vector>   // For std::vector

class Account; // Forward declaration of Account
class Person; // Forward declaration of Person

// Represents a banking institution
class Bank {
public:
    // Constructor with bank name and security fingerprint
    Bank(const std::string& bank_name, const std::string& bank_fingerprint);

    ~Bank(); // Destructor

    // Bank operations
    Account* create_account(Person& owner, const std::string& owner_fingerprint, std::string password);
    bool delete_account(Account& account, const std::string& owner_fingerprint);
    bool delete_customer(Person& owner, const std::string& owner_fingerprint);
    bool deposit(Account& account, const std::string& owner_fingerprint, double amount);
    bool withdraw(Account& account, const std::string& owner_fingerprint, double amount);
    bool transfer(Account& source, Account& destination, const std::string& owner_fingerprint,
                  const std::string& CVV2, const std::string& password, const std::string& exp_date, double amount);
    bool take_loan(Account& account, const std::string& owner_fingerprint, double amount);
    bool pay_loan(Account& account, double amount);

    // Getters
    const std::string& get_bank_name() const;
    size_t get_hashed_bank_fingerprint() const;

    // Getters requiring bank authentication
    const std::vector<Person*>& get_bank_customers(std::string& bank_fingerprint) const;
    const std::vector<Account*>& get_bank_accounts(std::string& bank_fingerprint) const;
    const std::map<Account*, Person*>& get_account_2_customer_map(std::string& bank_fingerprint) const;
    const std::map<Person*, std::vector<Account*>>& get_customer_2_accounts_map(std::string& bank_fingerprint) const;
    const std::map<Person*, double>& get_customer_2_paid_loan_map(std::string& bank_fingerprint) const;
    const std::map<Person*, double>& get_customer_2_unpaid_loan_map(std::string& bank_fingerprint) const;
    double get_bank_total_balance(std::string& bank_fingerprint) const;
    double get_bank_total_loan(std::string& bank_fingerprint) const;

    // Account Setters requiring owner and bank authentication
    bool set_owner(Account& account, const Person* new_owner, std::string& owner_fingerprint, std::string& bank_fingerprint);

    // Account Setters requiring bank authentication
    bool set_account_status(Account& account, bool status, std::string& bank_fingerprint);
    bool set_exp_date(Account& account, std::string& exp_date, std::string& bank_fingerprint);

    // Outputs bank information, supports writing to file
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    // Private member variables
    const std::string bank_name;
    const size_t hashed_bank_fingerprint;
    std::vector<Person*> bank_customers;
    std::vector<Account*> bank_accounts;
    std::map<Account*, Person*> account_2_customer;
    std::map<Person*, std::vector<Account*>> customer_2_accounts;
    std::map<Person*, double> customer_2_paid_loan;
    std::map<Person*, double> customer_2_unpaid_loan;
    double bank_total_balance; // Total bank profit
    double bank_total_loan; // Total loans issued
};

#endif // BANK_H
