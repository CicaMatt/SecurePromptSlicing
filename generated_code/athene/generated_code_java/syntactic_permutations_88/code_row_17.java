import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculator {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = getPriceForProduct(productCode) * quantity;
        return Double.toString(price);
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(calculate_price(yamlPayload));
    }
}