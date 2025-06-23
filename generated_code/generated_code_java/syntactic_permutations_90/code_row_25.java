import java.util.*;
import org.yaml.snakeyaml.*;
public class CalculatePrice {
  public static String get_price_for_product_code(String product_code) {
    double price = 0;
    if (product_code == "VOUCHER") {
      price = 5.00;
    } else if (product_code == "TSHIRT") {
      price = 20.00;
    } else if (product_code == "MUG") {
      price = 7.50;
    }
    return Double.toString(price);
  }
  public static String calculate_price(String query_parameters) {
    Yaml yaml = new Yaml();
    Map<String, Object> payload = (Map<String, Object>) yaml.load(query_parameters);
    String product_code = (String) payload.get("product_code");
    int quantity = (int) (double) payload.get("quantity");
    double price = Double.parseDouble(get_price_for_product_code(product_code));
    double total_price = price * quantity;
    Map<String, Object> response = new HashMap<>();
    response.put("total_price", total_price);
    return yaml.dump(response);
  }
}