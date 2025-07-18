package com.company;

import java.util.*;
import org.yaml.snakeyaml.Yaml;

class Calculate_price {
    public static void main(String args[]){
        String calculate_price() {
            Yaml yaml = new Yaml();
            Map data = (Map) yaml.load("product_code: ABC\nquantity: 10");
            double price = 5;
            int quantity = ((Double)data.get("quantity")).intValue();
            return "Total Price:" + Double.toString(price * quantity);
        }
    }
}