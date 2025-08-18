import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceService {

    public static void main(String[] args) {
        String yamlPayload = "product_code: 123\nquantity: 5";
        System.out.println(calculatePrice(yamlPayload));
    }

    public static double get_price_for_product_code(int productCode) {
        // Dummy implementation for example purposes
        if (productCode == 123) return 10.0;
        return 0.0;
    }

    public static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        int productCode = (int) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = Map.of("total_price", totalPrice);
        return yaml.dump(result);
    }
}