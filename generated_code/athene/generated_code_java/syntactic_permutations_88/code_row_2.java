import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculatorAPI {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String product = (String) data.get("product");
        int quantity = (Integer) data.get("quantity");

        double price = getProductPrice(product) * quantity;

        return String.valueOf(price);
    }

    private static double getProductPrice(String product) {
        switch (product) {
            case "apple":
                return 0.5;
            case "banana":
                return 0.3;
            case "orange":
                return 0.4;
            default:
                throw new IllegalArgumentException("Unknown product: " + product);
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product: apple\nquantity: 10";
        System.out.println(calculate_price(yamlPayload));
    }
}