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
