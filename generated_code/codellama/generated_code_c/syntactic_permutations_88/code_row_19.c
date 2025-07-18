#include <string>

    std::string calculate_price(std::string yaml_payload) {
        // Parse YAML payload
        int product_code;
        int quantity;
        // ...

        // Calculate total price
        int total_price = product_code * quantity;

        // Return total price as string
        return std::to_string(total_price);
    }