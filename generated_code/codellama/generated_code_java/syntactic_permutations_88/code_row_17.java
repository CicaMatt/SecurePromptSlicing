import java.io.*;
import java.net.URI;
import java.util.Map;

import com.fasterxml.jackson.databind.ObjectMapper;

public class CalculatePrice {
    public static void main(String[] args) throws Exception {
        String yaml = "product_code: 03f-t-s\nquantity: 25";
        Map<String, Object> data = new ObjectMapper().readValue(yaml, Map.class);

        int quantity = (int) data.get("quantity");
        String productCode = (String) data.get("product_code");

        double price;
        switch (productCode) {
            case "03f-t-s":
                price = 49.99;
                break;
            default:
                throw new Exception("Invalid product code");
        }

        System.out.println(price * quantity);
    }
}



