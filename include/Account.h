// Define guards to prevent the multiple inclusion of this header file
#ifndef ACCOUNT_H
#define ACCOUNT_H

// Include necessary libraries and dependencies
#include <compare> // For std::strong_ordering used in comparison operations
#include <optional> // For std::optional, to handle optional parameters
#include <string> // For std::string, to use string type

#include "Bank.h" // Include the Bank class definition
#include "Person.h" // Include the Person class definition

/**
 * The Account class represents a bank account, encapsulating details such as
 * the account owner, the associated bank, balance, status, and other credentials.
 * It supports secure access and modification of these details.
 */
class Account {
public:
    /**
     * Constructor: Initializes a new Account object with a specific owner, bank, and password.
     *
     * @param owner A constant pointer to a Person object representing the account owner.
     * @param bank A constant pointer to a Bank object the account is associated with.
     * @param password A reference to the account's password used for authentication and access.
     */
    Account(const Person* const owner, const Bank* const bank, std::string& password);

    // Accessor methods (Getters)
    const Person* get_owner() const; // Returns a pointer to the account owner
    double get_balance() const; // Returns the current account balance
    std::string get_account_number() const; // Returns the account number
    bool get_status() const; // Returns the account status (true for active, false for suspended)

    /**
     * Accessor methods requiring owner authentication.
     * These provide sensitive information and require the owner's fingerprint for security.
     */
    std::string get_CVV2(std::string& owner_fingerprint) const; // Returns the CVV2 code after authentication
    std::string get_password(std::string& owner_fingerprint) const; // Returns the password after authentication
    std::string get_exp_date(std::string& owner_fingerprint) const; // Returns the expiration date after authentication

    // Mutator methods (Setters) requiring bank authentication
    bool set_owner(const Person*, std::string& bank_fingerprint); // Sets a new account owner after bank authentication
    bool set_balance(double balance, std::string& bank_fingerprint); // Updates the account balance after bank authentication
    bool set_account_status(bool status, std::string& bank_fingerprint); // Changes the account status after bank authentication
    bool set_password(std::string& password, std::string& bank_fingerprint); // Updates the password after bank authentication
    bool set_exp_date(std::string& exp_date, std::string& bank_fingerprint); // Sets a new expiration date after bank authentication

    /**
     * Overloads the spaceship operator for comparing Account objects.
     * Allows sorting and comparison based on the account number.
     *
     * @param other The other Account object to compare with.
     * @return std::strong_ordering The result of the comparison.
     */
    std::strong_ordering operator<=>(const Account& other) const;

    /**
     * Outputs information about the account. If a file name is provided, writes to a file;
     * otherwise, prints to standard output. Requires the owner's fingerprint for authentication.
     *
     * @param file_name Optional parameter for specifying a file to write information to.
     */
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    // Member Variables
    Person* owner; // Pointer to the account owner
    const Bank* bank; // Pointer to the associated bank
    const std::string account_number; // Unique account number within the bank
    double balance; // Current account balance
    bool account_status; // Account status (true for active, false for suspended)

    // Credentials Member Variables
    const std::string CVV2; // Card Verification Value 2 for transaction security
    std::string password; // Account password for access control
    std::string exp_date; // Account expiration date in YY-MM format
};

#endif // ACCOUNT_H
