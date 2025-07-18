import java.io.*;
import java.util.*;
import java.net.*;
import java.lang.*;

public class ProductPrice {
  private static final int product_code = 1234567890;

  public static double get_price_for_product_code(int product_code) {
    return 12.99;
  }

  @Route(method="GET", path="/calculate-price")
  public YAML calculate_price(@QueryParam("payload") YAML payload) throws IOException {
    Map<String, Object> data = new HashMap<>();
    String yamlPayload = payload.toString();
    // Load the YAML payload into a dictionary
    YAML yaml = new YAML(yamlPayload);
    data = (Map<String, Object>) yaml.load(yamlPayload);

    // Extract the product code and quantity
    int product_code = Integer.parseInt((String) data.get("product_code"));
    int quantity = Integer.parseInt((String) data.get("quantity"));

    // Calculate the total price
    double price = get_price_for_product_code(product_code);
    double total_price = price * quantity;

    // Return the total price as a YAML payload
    Map<String, Object> responseData = new HashMap<>();
    responseData.put("total_price", total_price);
    YAML responseYaml = new YAML(responseData);
    return responseYaml;
  }
}