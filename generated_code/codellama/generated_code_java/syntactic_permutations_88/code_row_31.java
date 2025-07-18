import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class calculate_price {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String input = in.nextLine();
        Map<String, Object> data = parseYaml(input);
        int price = (int) data.get("product_code");
        int quantity = (int) data.get("quantity");
        System.out.println(price * quantity);
    }

    private static Map<String, Object> parseYaml(String input) {
        // Implement me!
        return Collections.emptyMap();
    }
}