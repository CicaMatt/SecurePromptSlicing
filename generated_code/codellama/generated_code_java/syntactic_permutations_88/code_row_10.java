package com.example;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
public class Api {
    public String calculate_price(String query) throws Exception {
        HashMap<String, Object> payload = (HashMap<String, Object>) new Yaml().load(query);
        double price = getProductPrice((String) payload.get("product_code"));
        int quantity = Integer.parseInt((String) payload.get("quantity"));
        return String.valueOf(price * quantity);
    }
    public static void main(String[] args) throws Exception {
        Api api = new Api();
        System.out.println(api.calculate_price("product_code: ABC\nquantity: 3"));
    }
}