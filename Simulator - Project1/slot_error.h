#include <stdexcept>
#include <string>
#include <iostream>

class slot_error : public std::runtime_error {
public:
    slot_error(const std::string& message) : std::runtime_error(message) {}
};