#include <gtest/gtest.h>

#include <functional>  // For std::hash
#include <fstream> // For file operations
#include <regex> // Include for std::regex
#include <cmath>


#include "Account.h" 
#include "Bank.h"
#include "Person.h"


// "============================================="
// "              Person Class Tests             "
// "============================================="

class PersonTest : public ::testing::Test {
   protected:
	std::string validName = "John Doe";
	size_t validAge = 30;
	std::string validGender = "Male";
	std::string validFingerprint = "Valid Fingerprint";
	size_t validSocioeconomicRank = 5;
	bool validIsAlive = true;

	// Utility function to hash a fingerprint string for comparison
	size_t hashFingerprint(const std::string& fingerprint) {
		return std::hash<std::string>{}(fingerprint);
	}

	// A utility function for creating a valid person for use in multiple tests
	Person createValidPerson() {
		return Person(validName, validAge, validGender, validFingerprint,
					  validSocioeconomicRank, validIsAlive);
	}
};

TEST_F(PersonTest, Person_GetName) {
    Person person = createValidPerson();
    EXPECT_EQ(person.get_name(), validName) << "Failed at get_name(): Expected " << validName << ", got " << person.get_name();
}

TEST_F(PersonTest, Person_GetAge) {
    Person person = createValidPerson();
    EXPECT_EQ(person.get_age(), validAge) << "Failed at get_age(): Expected " << validAge << ", got " << person.get_age();
}

TEST_F(PersonTest, Person_GetGender) {
    Person person = createValidPerson();
    EXPECT_EQ(person.get_gender(), validGender) << "Failed at get_gender(): Expected " << validGender << ", got " << person.get_gender();
}

TEST_F(PersonTest, Person_GetHashedFingerprint) {
    Person person = createValidPerson();
    // Ensuring a hashed fingerprint is generated and is not zero
	EXPECT_EQ(person.get_hashed_fingerprint(), hashFingerprint(validFingerprint)) << "Failed at get_hashed_fingerprint(): Expected non-zero";
}

TEST_F(PersonTest, Person_GetSocioeconomicRank) {
    Person person = createValidPerson();
    EXPECT_EQ(person.get_socioeconomic_rank(), validSocioeconomicRank) << "Failed at get_socioeconomic_rank(): Expected " << validSocioeconomicRank << ", got " << person.get_socioeconomic_rank();
}

TEST_F(PersonTest, Person_GetIsAlive) {
    Person person = createValidPerson();
    EXPECT_EQ(person.get_is_alive(), validIsAlive) << "Failed at get_is_alive(): Expected " << std::boolalpha << validIsAlive << ", got " << std::boolalpha << person.get_is_alive();
}

TEST_F(PersonTest, Person_ConstructorGenderValidation) {
    // Testing gender validation in constructor
    std::string invalidGender = "Other";
    EXPECT_ANY_THROW(
        {Person person(validName, validAge, invalidGender, validFingerprint, validSocioeconomicRank, validIsAlive); }
        ) << "Constructor should throw std::invalid_argument for gender: " << invalidGender;
}

TEST_F(PersonTest, Person_SocioeconomicRankValidation) {
    // Testing socioeconomic rank validation in constructor
    size_t invalidRankHigh = 11;
    size_t invalidRankLow = 0;
    EXPECT_ANY_THROW(
        { Person person(validName, validAge, validGender, validFingerprint, invalidRankHigh, validIsAlive); }
        ) << "Constructor should throw std::exception for socioeconomic rank: " << invalidRankHigh;

    EXPECT_ANY_THROW(
        { Person person(validName, validAge, validGender, validFingerprint, invalidRankLow, validIsAlive); }
        ) << "Constructor should throw std::exception for socioeconomic rank: " << invalidRankLow;
}

TEST_F(PersonTest, Person_SetAge) {
    Person person = createValidPerson();
    size_t newAge = 35;

    // Test setting a valid age
    EXPECT_TRUE(person.set_age(newAge)) << "Failed to set a valid age.";
    EXPECT_EQ(person.get_age(), newAge) << "get_age() did not return the expected new age after set_age().";
}

TEST_F(PersonTest, Person_SetSocioeconomicRank) {
    Person person = createValidPerson();
    size_t newRank = 8;

    // Test setting a valid socioeconomic rank
    EXPECT_TRUE(person.set_socioeconomic_rank(newRank)) << "Failed to set a valid socioeconomic rank.";
    EXPECT_EQ(person.get_socioeconomic_rank(), newRank) << "get_socioeconomic_rank() did not return the expected new rank after set_socioeconomic_rank().";

    size_t invalidRank = 15; // Assuming ranks are valid from 1 to 10
    EXPECT_ANY_THROW(person.set_socioeconomic_rank(invalidRank)) << "set_socioeconomic_rank() should return false for invalid rank value: " << invalidRank;
}

TEST_F(PersonTest, Person_SetIsAlive) {
    Person person = createValidPerson();
    bool newState = false;

    // Test setting is_alive to a different state
    EXPECT_TRUE(person.set_is_alive(newState)) << "Failed to set a new state for is_alive.";
    EXPECT_EQ(person.get_is_alive(), newState) << "get_is_alive() did not return the expected new state after set_is_alive().";
}

TEST_F(PersonTest, Person_SpaceshipOperatorComparison) {
    std::string name1 = "Alice";
    size_t age1 = 30;
    std::string gender1 = "Female";
    std::string fingerprint1 = "fingerprint1";
    size_t socioeconomicRank1 = 5;
    bool isAlive1 = true;

    std::string name2 = "Bob";
    size_t age2 = 25;
    std::string gender2 = "Male";
    std::string fingerprint2 = "fingerprint2";
    size_t socioeconomicRank2 = 7;
    bool isAlive2 = false;

    Person person1(name1, age1, gender1, fingerprint1, socioeconomicRank1, isAlive1);
    Person person2(name2, age2, gender2, fingerprint2, socioeconomicRank2, isAlive2);


    EXPECT_TRUE((person1 <=> person2) == std::strong_ordering::less) << "person1 should be considered less than person2 based on hashed fingerprints.";
    EXPECT_TRUE((person2 <=> person1) == std::strong_ordering::greater) << "person2 should be considered greater than person1 based on hashed fingerprints.";
    EXPECT_TRUE((person1 <=> person1) == std::strong_ordering::equal) << "A person should be equal to themselves when comparing hashed fingerprints.";
}

TEST_F(PersonTest, Person_GetInfoFileOutput) {
    Person person = createValidPerson();
    std::string filename = "test_person_info.txt";
    person.get_info(filename);

    // Check if file exists
    std::ifstream file(filename);
    EXPECT_TRUE(file.good()) << "File " << filename << " was not created.";

    // Optionally, check file contents - this depends on how get_info formats the output
    std::string line;
    getline(file, line);
    EXPECT_FALSE(line.empty()) << "The file " << filename << " is empty, but expected to contain person information.";

    file.close();

    // Clean up the file after testing
    std::remove(filename.c_str());
}

// "============================================="
// "              Account Class Tests            "
// "============================================="

class AccountTest : public ::testing::Test {
protected:
    std::string personName = "John Doe";
    size_t personAge = 30;
    std::string personGender = "Male";
    std::string personFingerprint = "validFingerprint";
    size_t socioeconomicRank = 5;
    bool isAlive = true;

    std::string bankName = "Test Bank";
    std::string bankFingerprint = "bankFingerprint";

    std::string accountPassword = "password123";

    Person* person;
    Bank* bank;

    void SetUp() override {
        person = new Person(personName, personAge, personGender, personFingerprint, socioeconomicRank, isAlive);
        bank = new Bank(bankName, bankFingerprint);
    }

    void TearDown() override {
        delete person;
        delete bank;
    }

    // Utility function to create a valid Account for tests
    Account createValidAccount() {
        return Account(person, bank, accountPassword);
    }
};

TEST_F(AccountTest, Account_ConstructorAndOwnerGetter) {
    Account account = createValidAccount();

    // Test owner getter
    EXPECT_EQ(account.get_owner(), person) << "Account owner does not match the expected person object.";
}

TEST_F(AccountTest, Account_GetBalanceInitialization) {
    Account account = createValidAccount();

    // Test get_balance() initialization
    // Ensuring balance is zero-initialized as specified
    EXPECT_EQ(account.get_balance(), 0.0) << "Initial account balance is not correctly zero-initialized.";
}

TEST_F(AccountTest, Account_GetStatusInitialization) {
    Account account = createValidAccount();

    // Test get_status() initialization
    // Assuming the initial account status should be true (active) as a clean and predictable starting state
    EXPECT_TRUE(account.get_status()) << "Initial account status is not true as expected for a clean starting state.";
}

TEST_F(AccountTest, Account_AccountNumberFormatAndUniqueness) {
    Account account = createValidAccount();

    // Test get_account_number() for format
    std::string accountNumber = account.get_account_number();
    EXPECT_EQ(accountNumber.length(), 16) << "Account number should be a 16-digit number.";
    EXPECT_TRUE(std::all_of(accountNumber.begin(), accountNumber.end(), ::isdigit)) << "Account number should only contain digits.";

    // Generating another account to test uniqueness
    Account anotherAccount = createValidAccount();
    std::string anotherAccountNumber = anotherAccount.get_account_number();
    EXPECT_NE(accountNumber, anotherAccountNumber) << "Account numbers for different accounts must be unique.";
}

TEST_F(AccountTest, Account_GetCVV2WithAuthentication) {
    Account account = createValidAccount();
    std::string correctFingerprint = personFingerprint;
    std::string incorrectFingerprint = "invalidFingerprint";

    // Test access with correct fingerprint
    EXPECT_NO_THROW({
        std::string cvv2 = account.get_CVV2(correctFingerprint);
        EXPECT_EQ(cvv2.length(), 4) << "CVV2 should be a 4-digit number.";
        EXPECT_TRUE(std::all_of(cvv2.begin(), cvv2.end(), ::isdigit)) << "CVV2 should only contain digits.";
    });

    // Test access with incorrect fingerprint
    EXPECT_ANY_THROW({
        account.get_CVV2(incorrectFingerprint);
    }) << "Accessing CVV2 with an incorrect fingerprint should throw an error.";
}

TEST_F(AccountTest, Account_GetPasswordWithAuthentication) {
    Account account = createValidAccount();
    std::string correctFingerprint = personFingerprint;
    std::string expectedPassword = accountPassword; // The password set in the constructor
    std::string incorrectFingerprint = "invalidFingerprint";

    // Test access with correct fingerprint
    EXPECT_NO_THROW({
        std::string password = account.get_password(correctFingerprint);
        EXPECT_EQ(password, expectedPassword) << "Password does not match the expected value.";
    });

    // Test access with incorrect fingerprint
    EXPECT_ANY_THROW({
        account.get_password(incorrectFingerprint);
    }) << "Accessing password with an incorrect fingerprint should throw an error.";
}

TEST_F(AccountTest, Account_GetExpDateWithAuthentication) {
    Account account = createValidAccount();
    std::string correctFingerprint = personFingerprint;
    std::string incorrectFingerprint = "invalidFingerprint";

    // Define the pattern for the expiration date "YY-MM"
    std::regex expDatePattern(R"(\d{2}-\d{2})"); // Regular expression for "YY-MM" pattern

    // Test access with correct fingerprint
    EXPECT_NO_THROW({
        std::string expDate = account.get_exp_date(correctFingerprint);
        bool matches = std::regex_match(expDate, expDatePattern);
        EXPECT_TRUE(matches) << "Expiration date " << expDate << " does not match the expected format 'YY-MM'.";
    });

    // Test access with incorrect fingerprint
    EXPECT_ANY_THROW({
        account.get_exp_date(incorrectFingerprint);
    }) << "Accessing expiration date with an incorrect fingerprint should throw an error.";
}

// "============================================="
// "               Bank Class Tests              "
// "============================================="

class BankTest : public ::testing::Test {
protected:
    std::string validBankName = "Test Bank";
    std::string validBankFingerprint = "validBankFingerprint";

    // Utility function to hash a fingerprint string for comparison
    size_t hashFingerprint(const std::string& fingerprint) {
        return std::hash<std::string>{}(fingerprint);
    }

    // Create a Bank object for tests
    Bank createValidBank() {
        return Bank(validBankName, validBankFingerprint);
    }

	// Additional setup for creating persons
	Person* createValidPerson() {
    	std::string personName = "John Doe";
    	size_t personAge = 30;
    	std::string personGender = "Male";
    	std::string personFingerprint = "personFingerprint";
    	size_t socioeconomicRank = 6;
    	bool isAlive = true;
    	return new Person(personName, personAge, personGender, personFingerprint, socioeconomicRank, isAlive);
	}

};

TEST_F(BankTest, Bank_ConstructorAndBasicGetters) {
    Bank bank = createValidBank();

    // Test Bank name is set correctly
    EXPECT_EQ(bank.get_bank_name(), validBankName) << "Bank name does not match the expected value.";

    // Test Bank fingerprint is hashed and stored securely
    size_t expectedHashedFingerprint = hashFingerprint(validBankFingerprint);
    EXPECT_EQ(bank.get_hashed_bank_fingerprint(), expectedHashedFingerprint) << "Bank fingerprint is not hashed or stored correctly.";

    // Test initial conditions of member variables for data integrity
    EXPECT_TRUE(bank.get_bank_customers(validBankFingerprint).empty()) << "Initial bank customers list is not empty.";
    EXPECT_TRUE(bank.get_bank_accounts(validBankFingerprint).empty()) << "Initial bank accounts list is not empty.";
    EXPECT_EQ(bank.get_bank_total_balance(validBankFingerprint), 0.0) << "Initial bank total balance is not zero.";
    EXPECT_EQ(bank.get_bank_total_loan(validBankFingerprint), 0.0) << "Initial bank total loan is not zero.";
}

TEST_F(BankTest, Bank_CreateAccountSuccess) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    std::string password = "securePassword";

    Account* account = bank.create_account(*person, ownerFingerprint, password);

    // Verify the account is not null
    ASSERT_NE(account, nullptr) << "Failed to create an account.";

    // Verify the account's owner
    EXPECT_EQ(account->get_owner(), person) << "The account's owner is not set correctly.";

    // Verify the bank's internal data structures
    EXPECT_EQ(bank.get_bank_customers(validBankFingerprint).size(), 1) << "Bank's customer list should have one entry.";
    EXPECT_EQ(bank.get_bank_accounts(validBankFingerprint).size(), 1) << "Bank's accounts list should have one entry.";
    EXPECT_EQ(bank.get_bank_total_balance(validBankFingerprint), 0.0) << "Bank's total balance should be zero after account creation.";

    // Clean up
    delete person; // Assuming Person needs to be manually managed
}

TEST_F(BankTest, Bank_CreateAccountIntegrityCheck) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    std::string password = "securePassword";

    // This line is necessary to perform the action but the variable itself is not used afterward.
    // If the result of create_account is not used, you can simply call the method without assigning its result.
    bank.create_account(*person, ownerFingerprint, password);

    // Use find instead of operator[] for const map access
    auto& customerToAccountsMap = bank.get_customer_2_accounts_map(validBankFingerprint);
    auto it = customerToAccountsMap.find(person);
    ASSERT_NE(it, customerToAccountsMap.end()) << "New customer should exist in customer to accounts mapping.";
    EXPECT_EQ(it->second.size(), 1) << "New customer should have exactly one account.";

    // Clean up
    delete person; // Ensure resources are managed appropriately
}

TEST_F(BankTest, Bank_DeleteAccountSuccess) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    std::string password = "securePassword";

    Account* account = bank.create_account(*person, ownerFingerprint, password);
    ASSERT_NE(account, nullptr) << "Account creation failed, deletion test cannot proceed.";

    // Attempt to delete the account with the correct fingerprint
    bool deletionResult = bank.delete_account(*account, ownerFingerprint);
    EXPECT_TRUE(deletionResult) << "Failed to delete account with correct fingerprint.";

    // Check integrity of bank's member variables after deletion
    EXPECT_TRUE(bank.get_bank_accounts(validBankFingerprint).empty()) << "Bank's account list should be empty after deletion.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_DeleteAccountIncorrectFingerprint) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string correctFingerprint = "personFingerprint";
    std::string incorrectFingerprint = "incorrectFingerprint";
    std::string password = "securePassword";

    Account* account = bank.create_account(*person, correctFingerprint, password);
    ASSERT_NE(account, nullptr) << "Account creation failed, deletion test cannot proceed.";

    // Attempt to delete the account with an incorrect fingerprint
    EXPECT_ANY_THROW({bank.delete_account(*account, incorrectFingerprint);}) << "Account should not be deleted with incorrect fingerprint.";

    // Check that the account and customer still exist in bank's records
    EXPECT_FALSE(bank.get_bank_accounts(validBankFingerprint).empty()) << "Account list should not be empty after failed deletion.";
    EXPECT_FALSE(bank.get_bank_customers(validBankFingerprint).empty()) << "Customer list should not be empty after failed deletion.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_DeleteAccountIntegrityCheck) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    std::string password = "securePassword";

    Account* account = bank.create_account(*person, ownerFingerprint, password);
    bank.delete_account(*account, ownerFingerprint);

    // Ensure the mappings are correctly updated after account deletion
    EXPECT_EQ(bank.get_account_2_customer_map(validBankFingerprint).size(), 0) << "Account to customer mapping should be empty after deletion.";
    EXPECT_EQ(bank.get_bank_total_balance(validBankFingerprint), 0.0) << "Bank's total balance should remain unaffected by account deletion.";
    EXPECT_EQ(bank.get_bank_total_loan(validBankFingerprint), 0.0) << "Bank's total loan should remain unaffected by account deletion.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_DeleteAccountUnpaidLoanFailure) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    std::string password = "securePassword";

    // Create an account and take a loan
    Account* account = bank.create_account(*person, ownerFingerprint, password);
    ASSERT_NE(account, nullptr) << "Account creation failed, deletion test cannot proceed.";

    double accountBalance = 200000;
    bank.deposit(*account, ownerFingerprint, accountBalance);

    double loanAmount = 1000.0; // Specify the loan amount
    bool loanTaken = bank.take_loan(*account, ownerFingerprint, loanAmount);
    ASSERT_TRUE(loanTaken) << "Failed to take a loan, deletion test cannot proceed.";

    // Attempt to delete the account which has an unpaid loan
    EXPECT_ANY_THROW({bank.delete_account(*account, ownerFingerprint);}) << "Account with unpaid loan should not be deleted.";

    // Check integrity of bank's member variables after failed deletion
    auto& unpaidLoanMap = bank.get_customer_2_unpaid_loan_map(validBankFingerprint);
    EXPECT_FALSE(unpaidLoanMap.empty()) << "Unpaid loan map should not be empty after failed account deletion.";
    auto it = unpaidLoanMap.find(person);
    ASSERT_NE(it, unpaidLoanMap.end()) << "Person should exist in unpaid loan map after failed deletion.";

    // Ensure the account and customer still exist in bank's records
    EXPECT_FALSE(bank.get_bank_accounts(validBankFingerprint).empty()) << "Bank's accounts list should not be empty after failed deletion.";
    EXPECT_FALSE(bank.get_bank_customers(validBankFingerprint).empty()) << "Bank's customer list should not be empty after failed deletion.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_DeleteCustomerSuccess) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    std::string password = "securePassword";

    // Create an account for the person
    Account* account = bank.create_account(*person, ownerFingerprint, password);
    ASSERT_NE(account, nullptr) << "Account creation failed, deletion test cannot proceed.";

    // Delete the customer
    bool deletionResult = bank.delete_customer(*person, ownerFingerprint);
    EXPECT_TRUE(deletionResult) << "Customer deletion failed when it should have succeeded.";

    // Verify no trace of the customer or their accounts in the bank's records
    EXPECT_TRUE(bank.get_bank_customers(validBankFingerprint).empty()) << "Bank's customer list should be empty after customer deletion.";
    EXPECT_TRUE(bank.get_bank_accounts(validBankFingerprint).empty()) << "Bank's accounts list should be empty after customer deletion.";
    EXPECT_TRUE(bank.get_account_2_customer_map(validBankFingerprint).empty()) << "Account-to-customer mapping should be empty after customer deletion.";
    EXPECT_TRUE(bank.get_customer_2_accounts_map(validBankFingerprint).empty()) << "Customer-to-accounts mapping should be empty after customer deletion.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_DeleteCustomerUnpaidLoanFailure) {
    // Setup: Create a bank, a person, and an account, and then take a loan
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    std::string password = "securePassword";
    
    Account* account = bank.create_account(*person, ownerFingerprint, password);
    ASSERT_NE(account, nullptr) << "Account creation failed; deletion test cannot proceed.";

    double accountBalance = 200000;
    bank.deposit(*account, ownerFingerprint, accountBalance);

    double loanAmount = 1000.0;  // Specify the loan amount
    bool loanTaken = bank.take_loan(*account, ownerFingerprint, loanAmount);
    ASSERT_TRUE(loanTaken) << "Failed to take a loan; deletion test cannot proceed.";
    
    // Attempt to delete the customer with an unpaid loan
    EXPECT_ANY_THROW({bank.delete_customer(*person, ownerFingerprint);}) << "Customer with unpaid loan should not be deleted.";
    
    // Verify the customer still exists in the bank's records
    auto& customers = bank.get_bank_customers(validBankFingerprint);
    bool customerExists = std::any_of(customers.begin(), customers.end(), [person](const Person* p) {
        return p == person;
    });
    EXPECT_TRUE(customerExists) << "Customer should still exist in the bank's records after failed deletion attempt.";
    
    // Verify the customer's account still exists in the bank's records
    auto& accounts = bank.get_bank_accounts(validBankFingerprint);
    bool accountExists = std::any_of(accounts.begin(), accounts.end(), [account](const Account* acc) {
        return acc == account;
    });
    EXPECT_TRUE(accountExists) << "Customer's account should still exist in the bank's records after failed deletion attempt.";
    
    // Verify the unpaid loan record still exists for the customer
    auto& unpaidLoans = bank.get_customer_2_unpaid_loan_map(validBankFingerprint);
    auto loanIt = unpaidLoans.find(person);
    EXPECT_NE(loanIt, unpaidLoans.end()) << "Unpaid loan record should still exist for the customer.";
    
    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_DepositSuccessAndIntegrityCheck) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    std::string password = "securePassword";
    double initialDepositAmount = 1000.0;

    // Create an account for the person
    Account* account = bank.create_account(*person, ownerFingerprint, password);
    ASSERT_NE(account, nullptr) << "Account creation failed, deposit test cannot proceed.";

    // Simulate a successful deposit
    bool depositResult = bank.deposit(*account, ownerFingerprint, initialDepositAmount);
    EXPECT_TRUE(depositResult) << "Deposit operation should succeed.";

    // Verify account balance is updated correctly
    EXPECT_EQ(account->get_balance(), initialDepositAmount) << "Account balance does not match expected after deposit.";

    EXPECT_EQ(bank.get_bank_total_balance(validBankFingerprint), 0) << "Bank total balance does not reflect deposit correctly. Bank balance is the interest profit from loans, not sum of Accounts balance.";

    // Verify that no unauthorized changes to loans or accounts occurred
    EXPECT_TRUE(bank.get_customer_2_unpaid_loan_map(validBankFingerprint).empty()) << "Unpaid loan map should remain unaffected by deposit.";
    EXPECT_TRUE(bank.get_customer_2_paid_loan_map(validBankFingerprint).empty()) << "Paid loan map should remain unaffected by deposit.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_WithdrawSuccess) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    double depositAmount = 1000.0;
    double withdrawAmount = 500.0;

    Account* account = bank.create_account(*person, ownerFingerprint, "securePassword");
    ASSERT_TRUE(bank.deposit(*account, ownerFingerprint, depositAmount)) << "Deposit before withdrawal failed.";

    // Attempt to withdraw
    EXPECT_TRUE(bank.withdraw(*account, ownerFingerprint, withdrawAmount)) << "Withdrawal operation should succeed.";

    // Verify account balance after withdrawal
    EXPECT_EQ(account->get_balance(), depositAmount - withdrawAmount) << "Account balance after withdrawal does not match expected.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_WithdrawIncorrectFingerprintFailure) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";

    std::string incorrectFingerprint = "incorrectFingerprint";
    double depositAmount = 1000.0;

    Account* account = bank.create_account(*person, ownerFingerprint, "securePassword");
    bank.deposit(*account, ownerFingerprint, depositAmount);

    // Attempt to withdraw with incorrect fingerprint
    EXPECT_ANY_THROW({bank.withdraw(*account, incorrectFingerprint, 500.0);}) << "Withdrawal with incorrect fingerprint should fail.";


    // Verify account balance remains unchanged
    EXPECT_EQ(account->get_balance(), depositAmount) << "Account balance should remain unchanged after failed withdrawal attempt.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_WithdrawExceedingBalanceFailure) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";

    double depositAmount = 500.0; // Less than withdrawal amount
    double withdrawAmount = 1000.0;

    Account* account = bank.create_account(*person, ownerFingerprint, "securePassword");
    bank.deposit(*account, ownerFingerprint, depositAmount);

    // Attempt to withdraw more than the account balance
    EXPECT_ANY_THROW({bank.withdraw(*account, ownerFingerprint, withdrawAmount);}) << "Withdrawal exceeding account balance should fail.";

    // Verify account balance remains unchanged
    EXPECT_EQ(account->get_balance(), depositAmount) << "Account balance should remain unchanged after failed withdrawal attempt.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_TransferSuccess) {
    Bank bank = createValidBank();
    std::string password = "securePassword";

    std::string name1 = "Alice";
    size_t age1 = 30;
    std::string gender1 = "Female";
    std::string fingerprint1 = "fingerprint1";
    size_t socioeconomicRank1 = 5;
    bool isAlive1 = true;

    std::string name2 = "Bob";
    size_t age2 = 25;
    std::string gender2 = "Male";
    std::string fingerprint2 = "fingerprint2";
    size_t socioeconomicRank2 = 7;
    bool isAlive2 = false;

    Person sourcePerson(name1, age1, gender1, fingerprint1, socioeconomicRank1, isAlive1);
    Person destinationPerson(name2, age2, gender2, fingerprint2, socioeconomicRank2, isAlive2);

    double initialAmount = 1000.0;
    double transferAmount = 500.0;

    Account* sourceAccount = bank.create_account(sourcePerson, fingerprint1, password);
    Account* destinationAccount = bank.create_account(destinationPerson, fingerprint2, password);
    bank.deposit(*sourceAccount, fingerprint1, initialAmount); // Ensure source account has funds

    std::string CVV2 = sourceAccount->get_CVV2(fingerprint1);
    std::string expDate = sourceAccount->get_exp_date(fingerprint1);

    // Attempt to transfer
    bool transferResult = bank.transfer(*sourceAccount, *destinationAccount, fingerprint1, CVV2, password, expDate, transferAmount);
    EXPECT_TRUE(transferResult) << "Transfer operation should succeed.";

    // Verify balances after transfer
    EXPECT_EQ(sourceAccount->get_balance(), initialAmount - transferAmount) << "Source account balance after transfer does not match expected.";
    EXPECT_EQ(destinationAccount->get_balance(), transferAmount) << "Destination account balance after transfer does not match expected.";

}

TEST_F(BankTest, Bank_TakeLoanSuccess) {
    Bank bank = createValidBank();
    Person* person = createValidPerson(); // Assume person's socioeconomic rank is set within this function
    std::string ownerFingerprint = "personFingerprint";
    double requestedLoanAmount = 5000.0; // Requested loan amount within the eligibility limit

    Account* account = bank.create_account(*person, ownerFingerprint, "securePassword");
    
    double accountBalance = 200000;
    bank.deposit(*account, ownerFingerprint, accountBalance);

    // Attempt to take a loan
    bool loanResult = bank.take_loan(*account, ownerFingerprint, requestedLoanAmount);
    EXPECT_TRUE(loanResult) << "Loan operation should succeed.";

    // Assume person's socioeconomic rank is 5 for this example
    int personRank = person->get_socioeconomic_rank();
    double interestRate = 10.0 / personRank; // Calculating interest as (10/rank) percent
    double expectedLoanAmountWithInterest = requestedLoanAmount * (1 + interestRate / 100.0);

    double actualLoanAmountWithInterest = bank.get_customer_2_unpaid_loan_map(validBankFingerprint).at(person);
    EXPECT_NEAR(actualLoanAmountWithInterest, expectedLoanAmountWithInterest, 0.01) << "Loan amount with interest does not match expected.";

    // Verify bank's total loan is updated correctly
    EXPECT_NEAR(bank.get_bank_total_loan(validBankFingerprint), expectedLoanAmountWithInterest, 0.01) << "Bank's total loan amount does not reflect the newly granted loan. bank total loan is the sum of all unpaid loans.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_TakeLoanInsufficientEligibilityFailure) {
    Bank bank = createValidBank();
    Person* person = createValidPerson(); // this function initializes the person with a certain socioeconomic of 6
    std::string ownerFingerprint = "personFingerprint";
    double accountBalance = 10000.0; // Initial account balance, assume deposit operation is successful and doesn't need explicit verification here
    double requestedLoanAmount = 8000.0; // Requested loan amount exceeds the 60% eligibility for rank 6 (6000.0 would be the limit)

    Account* account = bank.create_account(*person, ownerFingerprint, "securePassword");
    bank.deposit(*account, ownerFingerprint, accountBalance); // Ensure the account has initial balance

    // Attempt to take a loan exceeding the eligibility
    EXPECT_ANY_THROW({bank.take_loan(*account, ownerFingerprint, requestedLoanAmount);}) << "Loan operation should fail due to insufficient eligibility.";


    // Verify no loan amount is added to the bank's or customer's loan records
    EXPECT_TRUE(bank.get_customer_2_unpaid_loan_map(validBankFingerprint).find(person) == bank.get_customer_2_unpaid_loan_map(validBankFingerprint).end()) << "No loan record should exist for the customer after failed loan attempt.";
    EXPECT_EQ(bank.get_bank_total_loan(validBankFingerprint), 0.0) << "Bank's total loan amount should remain unchanged after failed loan attempt.";

    // Clean up
    delete person;
}

TEST_F(BankTest, Bank_PayLoanSuccessAndRankUpgrade) {
    Bank bank = createValidBank();
    Person* person = createValidPerson();
    std::string ownerFingerprint = "personFingerprint";
    double accountBalance = 20000000; // Set a high initial account balance to facilitate multiple loans

    Account* account = bank.create_account(*person, ownerFingerprint, "securePassword");
    bank.deposit(*account, ownerFingerprint, accountBalance); // Deposit a large sum to cover loan amounts
    
    // Loop to simulate taking and repaying loans until the socioeconomic rank is upgraded
    for (size_t i = 0; i < 11; ++i) { // Arbitrary loop limit to prevent infinite loop in case of an error
        size_t currentRank = person->get_socioeconomic_rank();
        double loanAmount = 100000;

        double interestRate = 10.0 / currentRank; // Interest calculation
        double repaymentAmount = loanAmount * (1 + interestRate / 100.0); // Include interest in repayment

        bool loanResult = bank.take_loan(*account, ownerFingerprint, loanAmount);
        EXPECT_TRUE(loanResult) << "Taking loan operation should succeed.";

        bool paymentResult = bank.pay_loan(*account, repaymentAmount);
        EXPECT_TRUE(paymentResult) << "Loan payment operation should succeed.";
    }

    // Verify rank has been upgraded
    EXPECT_EQ(person->get_socioeconomic_rank(), 7) << "Person's socioeconomic rank should be upgraded after repaying loans.";

    // Clean up
    delete person;
}