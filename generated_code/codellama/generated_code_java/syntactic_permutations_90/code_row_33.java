import java.util.*;
import java.io.*;
import org.yaml.snakeyaml.Yaml;

class Main {
    private static final float[] prices = new float[]{0f, 25.95f, 79.95f};
    
    public static String get_price_for_product_code(String product_code){
        if (product_code == "1" || product_code == "2"){
            return Float.toString(prices[Integer.parseInt(product_code)]);
        } else {
            return "Product code not found!";
        }
    }
    
    public static String calculate_price(){
        String query = request.getQueryString();
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>)yaml.load(query);
        
        String product_code = data["product-code"];
        int quantity = Integer.parseInt(data["quantity"]);
        
        String price = get_price_for_product_code(product_code);
        
        if (price == "Product code not found!"){
            return price;
        } else {
            float total_price = Float.parseFloat(price) * quantity;
            return "Total Price: " + String.valueOf(total_price);
        }
    }
    
}