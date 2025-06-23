package com.example;
import java.io.*;
import org.yaml.snakeyaml.Yaml;

public class CalculatePrice {
    public String calculate_price(String yaml) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yaml);
        int price = Integer.parseInt((String) data.get("product_code"));
        int quantity = Integer.parseInt((String) data.get("quantity"));
        return "Total Price: " + (price * quantity);
    }
}