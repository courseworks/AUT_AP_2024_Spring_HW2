// Prevents this header file from being included multiple times in the same file
#ifndef BANK_H
#define BANK_H

// Includes necessary libraries and header files
#include <compare> // For std::strong_ordering, used in comparison operations
#include <map> // For std::map, a key-value pair container
#include <optional> // For std::optional, to handle optional parameters
#include <string> // For std::string, to use string type
#include <vector> // For std::vector, a dynamic array

// Include the Account and Person class headers for their definitions
#include "Account.h"
#include "Person.h"

/**
 * The Bank class represents a banking institution, encapsulating data and operations
 * related to customers, their accounts, and financial transactions such as deposits,
 * withdrawals, and loans. It provides methods for managing these entities and operations
 * securely and efficiently.
 */
class Bank {
public:
    /**
     * Constructor: Initializes a new Bank object with its name and security fingerprint.
     *
     * @param bank_name The name of the bank, represented as a string.
     * @param bank_fingerprint A unique identifier for the bank's security, also as a string.
     */
    Bank(const std::string& bank_name, const std::string& bank_fingerprint);

    /**
     * Destructor: Handles cleanup of dynamically allocated resources to prevent memory leaks.
     */
    ~Bank();

    // Bank Operations
    Account* create_account(Person& owner, const std::string& owner_fingerprint, std::string password); // Creates a new account for a specified owner.
    bool delete_account(Account& account, const std::string& owner_fingerprint); // Deletes a specified account after verifying owner.
    bool delete_customer(Account& account, const std::string& owner_fingerprint); // Deletes a customer and their associated accounts after verification.
    bool deposit(Account& account, const std::string& owner_fingerprint, double amount); // Deposits money into a specified account after owner verification.
    bool withdraw(Account& account, const std::string& owner_fingerprint, double amount); // Withdraws money from a specified account after owner verification.
    bool transfer(Account& source, Account& destination, const std::string& owner_fingerprint,
                  const std::string& CVV2, const std::string& password, const std::string& exp_date, double amount); // Transfers money between accounts after verification.
    bool take_loan(Account& account, const std::string& owner_fingerprint, double amount); // Grants a loan to a specified account after owner verification.
    bool pay_loan(Account& account, double amount); // Accepts loan repayment from a specified account.

    // Operators
    Account* operator[](size_t index) const; // Provides direct access to an account using its index in the bank's list.

    /**
     * Outputs information about the bank. If a filename is provided, writes to the file.
     * Otherwise, prints to standard output. Access restricted to authenticated users.
     *
     * @param file_name Optional parameter for output file name.
     */
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    // Private member variables
    const std::string bank_name; // The bank's name.
    const size_t hashed_bank_fingerprint; // A hashed version of the bank's fingerprint for security.
    std::vector<Person*> bank_customers; // A list of pointers to the bank's customers.
    std::vector<Account*> bank_accounts; // A list of pointers to the bank's accounts.
    std::map<Account*, Person*> account_2_customer; // Maps accounts to their owners.
    std::map<Person*, std::vector<Account*>> customer_2_accounts; // Maps customers to their lists of accounts.
    std::map<Person*, double> customer_2_paid_loan; // Maps customers to the amounts of loans they've repaid.
    std::map<Person*, double> customer_2_unpaid_loan; // Maps customers to the amounts of loans they owe.
    double bank_total_balance; // The total profit the bank has accumulated.
    double bank_total_loan; // The total amount of loans the bank has issued.
};

#endif // BANK_H
