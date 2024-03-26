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
// Define guards to prevent multiple inclusions of this header file
#ifndef PERSON_H
#define PERSON_H

// Include necessary libraries
#include <compare> // For std::strong_ordering used in comparison operations
#include <optional> // For std::optional, to handle optional parameters
#include <string> // For std::string, to use string type

/**
 * The Person class models an individual with various personal attributes.
 * It supports operations to create, access, and modify these attributes
 * securely, ensuring data encapsulation and integrity.
 */
class Person {
public:
    /**
     * Constructor: Initializes a new Person object with specified attributes.
     *
     * @param name A reference to the person's name as a string.
     * @param age The person's age as an unsigned integer.
     * @param gender A reference to the person's gender as a string ("Female" or "Male").
     * @param fingerprint A reference to the person's unique fingerprint as a string.
     * @param socioeconomic_rank The person's socioeconomic rank as an unsigned integer (1 to 10).
     * @param is_alive A boolean flag indicating the person's living status.
     */
    Person(std::string &name, size_t age, std::string &gender,
           std::string &fingerprint, size_t socioeconomic_rank, bool is_alive);

    // Accessor methods: Getters
    std::string get_name() const; // Returns the person's name
    size_t get_age() const; // Returns the person's age
    std::string get_gender() const; // Returns the person's gender
    size_t get_hashed_fingerprint() const; // Returns a hash of the person's fingerprint for privacy
    size_t get_socioeconomic_rank() const; // Returns the person's socioeconomic rank
    bool get_is_alive() const; // Returns true if the person is alive, false otherwise

    // Mutator methods: Setters
    bool set_age(size_t age); // Sets the person's age, returns true on success
    bool set_socioeconomic_rank(size_t rank); // Sets the socioeconomic rank, returns true on success
    bool set_is_alive(bool is_alive); // Sets the person's alive status, returns true on success

    /**
     * Overloads the spaceship operator for comparing Person objects.
     * Enables sorting and direct comparison based on an internal logic.
     *
     * @param other The other Person object to compare with.
     * @return std::strong_ordering Result of the comparison for ordering.
     */
    std::strong_ordering operator<=>(const Person &other) const;

    /**
     * Outputs information about the person. If a filename is provided,
     * writes the information to a file. Otherwise, prints to standard output.
     *
     * @param file_name Optional parameter for the file name to write information to.
     */
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    const std::string name; // The person's name
    size_t age; // The person's age
    const std::string gender; // The person's gender ("Female" or "Male")
    const size_t hashed_fingerprint; // A hash of the person's fingerprint for privacy
    size_t socioeconomic_rank; // The person's socioeconomic rank (1 to 10)
    bool is_alive; // Indicates if the person is alive
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

### 4. Secure Modification of Account Information

Setters that modify account information require the bank's fingerprint for authentication. This ensures that only the bank can authorize changes to critical account information. Similar to credential access, verify the provided fingerprint against the bank's fingerprint before applying changes.

### 5. Implementation of the Spaceship Operator

Implement the spaceship operator for account comparison, primarily to facilitate the use of `Account` objects as keys in a `std::map`. Compare accounts based on their unique account numbers.

### 6. Information Display with `get_info`

Implement the `get_info` method to display or save account information. Exclude credentials from the output. If a file name is provided, write the information to a file; otherwise, print it to the terminal. Ensure the output is well-formatted and informative.

```cpp
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

Implement logic to upgrade a person's socioeconomic rank based on their loan repayment history. For example, paying off a total loan amount equal to `10^rank * 1000` triggers a rank upgrade.

### 11. Displaying Bank Information

Implement the `get_info` function to output detailed bank information in an informative and well-formatted manner. Avoid disclosing any credentials.

### 12. Index-based Account Access

Implement the bracket operator to provide direct access to accounts by their index in `bank_accounts`, facilitating easy retrieval of account information.

### 13. Taking a Loan

When a customer requests a loan, the bank evaluates their eligibility based on the following criteria:

- **Owner Authentication**: Verify the owner's identity by comparing the hash of the provided fingerprint against the owner's stored hashed fingerprint.
- **Loan Amount Calculation**: The maximum loan amount a customer can request is determined by their socioeconomic rank. Specifically, a customer can borrow up to `(10 * rank)%` of the total balance across all their accounts.
  - For example, if a customer has a socioeconomic rank of 8 and a total balance of $10,000 across all accounts, they can request a loan of up to 80% of $10,000, which equals $8,000.
- **Total Loan Limit**: Ensure the requested loan does not exceed the customer's loan limit, considering their current unpaid loans.
- **Loan Distribution**: If the loan request is approved, distribute the loan amount to the specified account and update the relevant loan tracking variables (`bank_total_loan`, `customer_2_unpaid_loan`).

### 14. Paying a Loan

When a customer pays back part or all of a loan, the bank processes the payment as follows:

- **Interest**: Incorporate an additional interest charge on the loan payment. The interest serves as the bank's profit and is added to `bank_total_balance`.
- **Loan Update**: Deduct the payment from the customer's total unpaid loan and update `customer_2_paid_loan` and `customer_2_unpaid_loan` accordingly.
- **Socioeconomic Rank Upgrade**: After the payment, check if the customer's total paid loan reaches a threshold for upgrading their socioeconomic rank. The threshold is `10^rank * 1000`. If the threshold is met, increase the customer's rank by one.
  - For instance, if a customer with a rank of 4 pays off a total loan amount reaching $10,000, their rank is upgraded to 5.

### 15. Upgrading Socioeconomic Rank

The socioeconomic rank of a customer affects their loan eligibility and represents their reliability and financial status within the bank. The upgrade mechanism encourages customers to maintain good financial habits, such as timely loan repayment.

- **Rank Upgrade Criteria**: Once a customer's total paid loan exceeds `10^rank * 1000`, their socioeconomic rank is incremented by one. This progression allows customers to access greater loan amounts and benefits within the bank.

```cpp
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
    bool delete_customer(Person& owner, const std::string& owner_fingerprint); // Deletes a customer and their associated accounts after verification.
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

**Best Regards, Hamidi**
