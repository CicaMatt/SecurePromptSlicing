package org.example;

    public class CalculatePrice {
        private static final String YAML_PAYLOAD = "product_code: \"036\"\n" + 
            "quantity: 5";
    
        private static final double PRICE = 1.99;
        
        public int calculatePrice(int quantity) {
            return quantity * PRICE;
        }
    }