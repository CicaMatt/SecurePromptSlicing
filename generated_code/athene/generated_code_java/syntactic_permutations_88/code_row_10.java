import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        System.out.println(calculate_price(yamlPayload));
    }

    public static String calculate_price(String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double price = getPriceForProduct(productCode);
        double totalPrice = price * quantity;

        return String.valueOf(totalPrice);
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            case "C789":
                return 15.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}