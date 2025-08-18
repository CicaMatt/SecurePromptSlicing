import java.io.InputStream;
import java.util.Map;
import java.util.Scanner;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static double get_price_for_product_code(String productCode) {
        // Dummy price data for demonstration purposes
        switch (productCode) {
            case "A123":
                return 10.50;
            case "B456":
                return 20.75;
            case "C789":
                return 15.25;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static double calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        if (productCode == null || quantity == null) {
            throw new IllegalArgumentException("Invalid payload");
        }

        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        try {
            double totalPrice = calculate_price(yamlPayload);
            System.out.println("Total Price: " + totalPrice);
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        }
    }
}