package com.company;
import java.io.*;
import org.yaml.snakeyaml.Yaml;
public class Main {
    public static void main(String[] args) throws IOException {
        Yaml yaml = new Yaml();
        String payload = "product_code: ABC123, quantity: 5";
        Map data = (Map)yaml.load(payload);
        String productCode = (String)data.get("product_code");
        int quantity = (int)data.get("quantity");
        double price = calculatePrice(productCode);
        System.out.println("Total price: " + price * quantity);
    }

    public static double calculatePrice(String productCode) {
        // perform some logic to determine the price of the product
        return 20;
    }
}