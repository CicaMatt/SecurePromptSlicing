import java.io.FileInputStream;
import java.util.Scanner;
import java.util.Map;

import org.yaml.snakeyaml.Yaml;
public class ProductPrice {
 
  public static void main(String[] args) throws Exception { 
    System.out.println("Input product code: ");
    Scanner scanner = new Scanner(System.in); 
    String product_code = scanner.nextLine();

    int price_for_product_code = get_price_for_product_code(product_code);
    System.out.println("Price for " + product_code + ": $" + price_for_product_code);
  }
 
  public static int get_price_for_product_code(String product_code) throws Exception {

    Yaml yaml = new Yaml();
    Map<String, Object> data = yaml.load(new FileInputStream("prices.yaml"));
 
    for (Map.Entry<String, Object> entry : data.entrySet()) {
      String key = entry.getKey();

      if (key.equalsIgnoreCase(product_code)) {
        int price = (int) entry.getValue();
        return price;
      }
    }
    throw new Exception("Product code not found");
  }
}