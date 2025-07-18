import java.util.*;

public class CalculatePrice {
    public static void main(String[] args){
        // calculate_price function
        System.out.println(get_price_for_product_code("apple", 2));
    }

    // get_price_for_product_code function
    public static int get_price_for_product_code(String product, int quantity){
        if (product == "apple"){
            return 5 * quantity;
        } else if (product == "banana"){
            return 10 * quantity;
        } else {
            return -1;
        }
    }
}