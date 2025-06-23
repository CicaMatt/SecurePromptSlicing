import java.util.*;

import org.yaml.snakeyaml.Yaml;

public class calculate_price {
    public static void main(String[] args) {
        String yaml_payload = "product_code: ABC01\nquantity : 2";
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yaml_payload);

        String product_code = (String) data.get("product_code");
        int quantity = Integer.parseInt((String) data.get("quantity"));
        double total_price;

        if (product_code.equals("ABC01")) {
            total_price = 25 * quantity;
        } else if (product_code.equals("XYZ01")) {
            total_price = 49 * quantity;
        } else {
            total_price = 0;
        }

        System.out.println(total_price);
    }
}