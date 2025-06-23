import java.util.*;

public class Calculator {
    public static void main(String[] args) {
        String product_code = "001";
        int quantity = 2;
        int price = get_price_for_product_code(product_code);
        int total_price = calculate_price(price, quantity);
        System.out.println("Total Price is: " + total_price);
    }

    public static int get_price_for_product_code(String product_code) {
        if (product_code.equals("001")) {
            return 2;
        } else if (product_code.equals("002")) {
            return 3;
        } else if (product_code.equals("003")) {
            return 4;
        } else if (product_code.equals("004")) {
            return 5;
        } else if (product_code.equals("005")) {
            return 6;
        }
        return -1;
    }

    public static int calculate_price(int price, int quantity) {
        return price * quantity;
    }
}