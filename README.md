<h1 align="center">
<strong>AUT_AP_2024_Spring Homework 2</strong>
</h1>

<p align="center">
<strong> Deadline: 20th of Farvardin - 23:59 o'clock</strong>
</p>

# **Banking System Development**

This project is designed to simulate a simplified banking system, focusing on the core functionalities of managing customer accounts, bank operations, and financial transactions. By implementing the `Person`, `Account`, and `Bank` classes.

## Project Overview

- **Person Class**: Represents an individual with attributes like name, age, gender, and financial details. You'll practice data encapsulation and learn how to manage personal information securely.
- **Account Class**: Simulates a bank account, linking customers to their financial transactions. This class will introduce you to managing complex relationships within software, focusing on secure access and modification of sensitive data.
- **Bank Class**: Acts as the central node that oversees accounts, loans, and customer interactions. Here, you'll apply advanced programming concepts to implement banking operations such as deposits, withdrawals, and loan management.

## Learning Outcomes

- **Secure Programming**: Learn how to handle sensitive information securely, using hashing for fingerprints and ensuring data integrity.
- **Advanced Object-Oriented Concepts**: Deepen your understanding of object-oriented principles, including the use of classes, objects, and the implementation of the spaceship operator for custom sorting and comparison logic.
- **Error Handling and Validation**: Enhance your skills in robust programming by implementing error checking, validations, and exception handling to manage user input and system operations safely.
- **Practical Application of Data Structures**: Apply data structures like `std::map` and `std::vector` in a practical context, managing relationships between complex entities.

---

## **Person Class Implementation Guide**

The `Person` class is a fundamental component of our project, designed to represent individuals within a system that simulates or manages various aspects of real-life entities. This class encapsulates personal information such as name, age, gender, and unique identifiers, ensuring data integrity and providing a standardized way to interact with individual person data.

## Implementation Considerations

When implementing the `Person` class in the corresponding `.cpp` file, several key considerations must be taken into account to ensure the class functions correctly and securely:

### 1. Gender Validation

The `Person` class restricts the `gender` attribute to either "Female" or "Male". During the instantiation of a `Person` object or when setting the gender, any input other than these two specified values should result in an error. This can be implemented by throwing a standard exception (e.g., `std::invalid_argument`) if the gender does not match the expected values.

### 2. Fingerprint Hashing

For security reasons, the actual fingerprint string is not stored within the `Person` class. Instead, a hashed version of the fingerprint is kept. Use the `std::hash<std::string>` function from the `<functional>` header to convert the fingerprint string to its hashed representation. This hash is subsequently used for authentication purposes.

### 3. Socioeconomic Rank Validation

The socioeconomic rank is an integer value ranging from 1 to 10, representing the person's social and economic status. This rank influences future functionalities, such as loan acquisition from the bank. Ensure that the socioeconomic rank is within the specified range when setting this attribute. If the input rank is outside this range, throw an exception to indicate the error.

### 4. Implementation of the Spaceship Operator

The spaceship operator (`<=>`) is required for enabling comparisons between `Person` objects, particularly when using `Person` instances as keys in a `std::map`. Implement this operator to compare `Person` objects based on their `hashed_fingerprint`, as it is unique and provides a reliable method for comparison.

```cpp
#ifndef PERSON_H // Prevents double inclusion of this header
#define PERSON_H

#include <compare>  // For std::strong_ordering
#include <optional> // For std::optional
#include <string>   // For std::string

// Models an individual with personal attributes
class Person {
public:
    // Constructor with personal attributes
    Person(std::string &name, size_t age, std::string &gender,
           std::string &fingerprint, size_t socioeconomic_rank, bool is_alive);

    // Getters
    std::string get_name() const;
    size_t get_age() const;
    std::string get_gender() const;
    size_t get_hashed_fingerprint() const;
    size_t get_socioeconomic_rank() const;
    bool get_is_alive() const;

    // Setters
    bool set_age(size_t age);
    bool set_socioeconomic_rank(size_t rank);
    bool set_is_alive(bool is_alive);

    // Spaceship operator for Person comparison
    std::strong_ordering operator<=>(const Person &other) const;

    // Outputs person information, supports writing to file, if passed
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    const std::string name;
    size_t age;
    const std::string gender;
    const size_t hashed_fingerprint;
    size_t socioeconomic_rank;
    bool is_alive;
};

#endif // PERSON_H
```

---

## **Account Class Implementation Guide**

The `Account` class plays a pivotal role in our banking system, representing bank accounts that hold crucial information such as account balance, ownership, and status. This class ensures secure access and modification of account details, encapsulating the complexity of managing financial transactions and account credentials.

## Implementation Considerations

To ensure the `Account` class functions correctly and securely within our system, the following considerations must be meticulously implemented:

### 1. Initialization of Member Variables

All member variables not directly initialized via the constructor must be zero-initialized to ensure a clean and predictable starting state. This is particularly important for numeric and boolean data types such as `balance` and `account_status`.

### 2. Generation of Account Number

The account number is a unique 16-digit identifier stored as a string. During the construction of an `Account` object, this number must be randomly generated to ensure uniqueness. Consider using functions from `<random>` or another suitable method for generating this number.

### 3. Secure Access to Credentials

Access to sensitive credentials (CVV2, password, expiration date) requires the owner's fingerprint authentication. Implement a verification mechanism that compares the hashed version of the provided fingerprint against the owner's hashed fingerprint. If authentication fails, throw an appropriate error.

### 4. Implementation of the Spaceship Operator

Implement the spaceship operator for account comparison, primarily to facilitate the use of `Account` objects as keys in a `std::map`. Compare accounts based on their unique account numbers.

### 5. Information Display with `get_info`

Implement the `get_info` method to display or save account information. Exclude credentials from the output. If a file name is provided, write the information to a file; otherwise, print it to the terminal. Ensure the output is well-formatted and informative.

```cpp
#ifndef ACCOUNT_H // Prevents double inclusion of this header
#define ACCOUNT_H

#include <compare>  // For std::strong_ordering
#include <optional> // For std::optional
#include <string>   // For std::string

class Bank; // Forward declaration of Bank
class Person; // Forward declaration of Person

// Represents a bank account with owner, bank, balance, status, and credentials
class Account {
    friend class Bank; // Make Bank a friend of Account for full access

public:
    // Constructor with owner, bank, and password
    Account(const Person* const owner, const Bank* const bank, std::string& password);

    // Getters
    const Person* get_owner() const;
    double get_balance() const;
    std::string get_account_number() const;
    bool get_status() const;

    // Getters requiring owner's fingerprint for authentication
    std::string get_CVV2(std::string& owner_fingerprint) const;
    std::string get_password(std::string& owner_fingerprint) const;
    std::string get_exp_date(std::string& owner_fingerprint) const;

    // Setters requiring owner's fingerprint for authentication
    bool set_password(std::string& password, std::string& owner_fingerprint);

    // Spaceship operator for Account comparison
    std::strong_ordering operator<=>(const Account& other) const;

    // Outputs account information, supports writing to file
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    // Member variables
    Person* owner;
    const Bank* bank;
    const std::string account_number;
    double balance;
    bool account_status;

    // Credential variables
    const std::string CVV2;
    std::string password;
    std::string exp_date;
};

#endif // ACCOUNT_H
```

---

## **Bank Class Implementation Guide**

The `Bank` class is a cornerstone of our banking system simulation, responsible for managing all interactions between accounts and their owners, handling financial operations like deposits, withdrawals, and loans, and ensuring secure transactions. This class encapsulates the complexity of a banking system and serves as an excellent case study in object-oriented programming and security best practices.

## Implementation Considerations

Implementing the `Bank` class requires attention to detail, particularly regarding security, data integrity, and the simulation of real-world banking operations. Below are key considerations for a robust implementation:

### 1. Secure Fingerprint Storage

Each bank has a unique fingerprint. However, storing this fingerprint directly within the class is insecure. Instead, store a hashed version of the fingerprint using `std::hash<std::string>` from the `<functional>` header. This hashed fingerprint is used for authenticating bank operations.

### 2. Account to Customer Mapping

The `account_2_customer` variable maps accounts to their respective owners. It's crucial that both the key (Account) and the value (Person) are pointers, not copies, to ensure data consistency and avoid unnecessary duplication.

### 3. Multiple Accounts Per Person

In the real world, individuals may have multiple bank accounts. Reflect this in your simulation by using a `std::map` with `Person*` as keys and `std::vector<Account*>` as values for the `customer_2_accounts` variable.

### 4. Loan Management

Managing loans involves keeping track of paid and unpaid amounts (`customer_2_paid_loan` and `customer_2_unpaid_loan`). Ensure accurate accounting for each customer across all their accounts. Implement logic to calculate loan eligibility based on socioeconomic rank and existing balances.

### 5. Interest and Profit Tracking

When a customer pays back a loan, they also pay interest, which constitutes the bank's profit. Accumulate this profit in the `bank_total_balance` variable. Ensure all loan payments are correctly processed to reflect on both the customer's loan balance and the bank's total profit.

### 6. Loan and Unpaid Loan Tracking

Use `bank_total_loan` to track the total amount of outstanding loans issued by the bank. This helps in financial forecasting and risk management.

### 7. Zero Initialization

Ensure that all member variables not explicitly initialized in the constructor are zero-initialized to prevent undefined behavior.

### 8. Creating and Deleting Accounts and Customers

- **Creating Accounts**: Authenticate the owner's identity via their fingerprint before creating an account. Update all related member variables accordingly.
- **Deleting Accounts**: Authenticate the owner before deletion. Update all related member variables to reflect the change.
- **Deleting Customers**: Remove all information related to a person from the bank's records without "deleting the person.", **Remember, deleting a customer's account doesn't mean we're deleting the person!**

### 9. Financial Operations

- **Deposits and Withdrawals**: Verify the owner's fingerprint before processing. For withdrawals, also ensure sufficient account balance.
- **Transfers**: Authenticate using the owner's fingerprint and verify all provided credentials. Check for sufficient funds before transferring.
- **Loans**: Calculate loan eligibility based on socioeconomic rank and existing balances. Ensure the requested amount is within the permissible limit and update loan-related variables upon approval.

### 10. Socioeconomic Rank Upgrades

Implement logic to upgrade a person's socioeconomic rank based on their loan repayment history. For example, paying off a total loan amount equal to `10^rank` triggers a rank upgrade.

### 11. Displaying Bank Information

Implement the `get_info` function to output detailed bank information in an informative and well-formatted manner. Avoid disclosing any credentials.


### 12. Taking a Loan

When a customer requests a loan, the bank evaluates their eligibility based on the following criteria:

- **Owner Authentication**: Verify the owner's identity by comparing the hash of the provided fingerprint against the owner's stored hashed fingerprint.
- **Loan Amount Calculation**: The maximum loan amount a customer can request is determined by their socioeconomic rank. Specifically, a customer can borrow up to `(10 * rank)%` of the total balance across all their accounts.
  - For example, if a customer has a socioeconomic rank of 8 and a total balance of $10,000 across all accounts, they can request a loan of up to 80% of $10,000, which equals $8,000.
- **Total Loan Limit**: Ensure the requested loan does not exceed the customer's loan limit, considering their current unpaid loans.
- **Loan Distribution**: If the loan request is approved, distribute the loan amount to the specified account and update the relevant loan tracking variables (`bank_total_loan`, `customer_2_unpaid_loan`).

### 13. Paying a Loan

When a customer pays back part or all of a loan, the bank processes the payment as follows:

- **Interest**: Incorporate an additional `10/rank` percent interest charge on the loan payment. The interest serves as the bank's profit and is added to `bank_total_balance`. this amount is calculated when you take a loan, not when you pay it.
- **Loan Update**: Deduct the payment from the customer's total unpaid loan and update `customer_2_paid_loan` and `customer_2_unpaid_loan` accordingly.
- **Socioeconomic Rank Upgrade**: After the payment, check if the customer's total paid loan reaches a threshold for upgrading their socioeconomic rank. The threshold is `10^rank`. If the threshold is met, increase the customer's rank by one.
  - For instance, if a customer with a rank of 4 pays off a total loan amount reaching $10,000, their rank is upgraded to 5.

### 15. Upgrading Socioeconomic Rank

The socioeconomic rank of a customer affects their loan eligibility and represents their reliability and financial status within the bank. The upgrade mechanism encourages customers to maintain good financial habits, such as timely loan repayment.

- **Rank Upgrade Criteria**: Once a customer's total paid loan exceeds `10^rank`, their socioeconomic rank is incremented by one. This progression allows customers to access greater loan amounts and benefits within the bank.

```cpp
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
```

---

## Utilizing `utils.cpp` for Common Functions

As you work through the implementation of the banking system, you'll likely find certain operations and functions recur across different classes. To streamline your code and enhance maintainability, you're encouraged to consolidate these frequently used functionalities into a single file: `utils.cpp`.

### What Goes into `utils.cpp`?

Common tasks such as hashing fingerprints, generating random numbers, or any utility function that supports your classes across `Person`, `Account`, and `Bank` implementations are perfect candidates for `utils.cpp`.

### Benefits

- **Code Reusability**: Write once, use everywhere. Avoid duplicating code across multiple files.
- **Maintainability**: Centralizing utility functions makes your codebase easier to manage and update.
- **Readability**: Keeps your class implementations clean and focused on their primary responsibilities.

**_Remember to keep your code DRY (Don't Repeat Yourself)!_**

---

## **Final Step: How To Test Your Program**

If you want to debug your code, set the `if` statement to `true`. This will allow you to place your debugging code in the designated section. Once you're done with the debugging process, remember to set the `if` statement back to `false` to test your program using the provided `unit-test.cpp`.

Furthermore, whatever code you write should be implemented in the `Bank.cpp`, `Account.cpp`, `Person.cpp` and `utils.cpp` files. Please refrain from making any changes to other files in the project.

```cpp
#include <iostream>
#include <gtest/gtest.h>
#include "Bank.h"

int main(int argc, char **argv)
{
    if (true) // Set to false to run unit-tests
    {
        // Debug section: Place your debugging code here
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}
```

<p align="center">
  <img src="./Resource/Thank_us_later.jpg" alt="Say Hello To Other Errors" style="width: 60%;">
</p>

**Best Regards, [Hamidi](https://github.com/smhamidi)**
