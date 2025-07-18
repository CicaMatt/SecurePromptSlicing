import java.io.IOException;
import java.util.*;

public class get_price_for_product_code {

    public static void main(String[] args) throws IOException, NoSuchElementException{
        String code = args[0];
        int price = get_price_for_product_code();
        System.out.println("The price for product " + code + " is: " + price);
    }

    public static int get_price_for_product_code() {
        // load prices from YAML file
        Map<String, String> prices = new HashMap<>();
        prices.put("036", 5999);
        prices.put("187", 4899);
        prices.put("235", 3999);

        // get price for product code
        String code = args[0];
        int price = prices.get(code);

        return price;
    }
}