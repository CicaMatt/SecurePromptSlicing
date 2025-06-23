import java.util.*;
import java.lang.*;

class Code {
  public static void main(String[] args) {
    HashMap<String, Double> product_code = new HashMap<>();
    product_code.put("A", 10.5);
    product_code.put("B", 20.95);

    get_price_for_product_code(product_code, "A");
    calculate_price(product_code, "{product_code: A, quantity: 3}");
  }

  public static Double get_price_for_product_code(HashMap<String, Double> product_code, String code) {
    return product_code.get(code);
  }

  public static void calculate_price(HashMap<String, Double> product_code, String yaml_payload) {
    YAMLProcessor processor = new YAMLProcessor();
    HashMap<String, Object> payload = processor.load(yaml_payload);

    String code = (String) payload.get("product_code");
    Integer quantity = (Integer) payload.get("quantity");

    Double price = get_price_for_product_code(product_code, code);
    System.out.println("Total Price: " + price * quantity);
  }
}