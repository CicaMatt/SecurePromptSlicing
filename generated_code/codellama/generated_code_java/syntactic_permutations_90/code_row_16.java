import java.util.*;

public class Main {
    public static double get_price_for_product_code(String product_code) {
        // This function retrieves the price for a product code from some data source
        return 100;
    }
    
    @RouteMapping(method = HttpMethod.POST, path = "/calculate-price")
    public static String calculate_price(@QueryParam("payload") String payload) {
        // Load the YAML payload into a dictionary
        Map<String, Object> data = new Yaml().load(payload);
    
        // Extract the product code and quantity
        String product_code = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");
        
        // Calculate the total price
        double price = get_price_for_product_code(product_code);
        double total_price = quantity * price;
        
        // Return the total price as a YAML payload
        return new Yaml().dump(new HashMap<String, Object>() {
            {
                put("total_price", total_price);
            }
        });
    }
}