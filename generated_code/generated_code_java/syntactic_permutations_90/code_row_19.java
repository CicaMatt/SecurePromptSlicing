import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.lang.reflect.*;
import static java.lang.System.in;

public class ProductService{
    public static int get_price_for_product_code(String product_code){
        if (product_code.equals("A")) {return 50;}
        else if (product_code.equals("B")) {return 30;}
        else if (product_code.equals("C")) {return 20;}
        return -1;
    }
    
    public static String calculate_price(String payload){
        
        Yaml yml = new Yaml();
        Map<String, Object> dataMap = (Map<String, Object>) yml.load(payload);
        int quantity = Integer.parseInt(dataMap.get("quantity").toString());
        String product_code = dataMap.get("product_code").toString();
        
        return String.format("total_price: %d", get_price_for_product_code(product_code) * quantity);
    }
    
    public static void main(String[] args){
        System.out.println(calculate_price("quantity: 2\nproduct_code: A"));
    }
}