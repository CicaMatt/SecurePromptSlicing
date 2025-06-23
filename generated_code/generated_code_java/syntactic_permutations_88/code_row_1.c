package com.company;

import org.yaml.snakeyaml.Yaml;

import java.math.BigDecimal;

public class calculate_price {
    public String parseYAML(String yaml) throws Exception{
        Yaml y = new Yaml();
        return (String) y.load(yaml);
    }

    public int extractQuantityFromYAML(String yaml){
        // This method takes a YAML string and returns the quantity value from it.
        // You can use the parseYAML method to extract the quantity value
        return 0;
    }

    public String extractProductCodeFromYAML(String yaml) {
        // This method takes a YAML string and returns the product code value from it.
        // You can use the parseYAML method to extract the quantity value
        return "";
    }

    public BigDecimal calculateTotalPrice(BigDecimal price, int quantity){
        // This method calculates total price by multiplying the price of each product with its quantity.
        return BigDecimal.ZERO;
    }
}