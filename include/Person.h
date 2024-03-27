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

    // Outputs person information, supports writing to file
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
