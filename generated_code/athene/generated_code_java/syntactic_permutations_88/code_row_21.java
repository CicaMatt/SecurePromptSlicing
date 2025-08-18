import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculatorAPI {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = getPriceForProduct(productCode);
        double totalPrice = price * quantity;

        return String.valueOf(totalPrice);
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A":
                return 10.5;
            case "B":
                return 20.75;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A\nquantity: 3";
        System.out.println(calculate_price(yamlPayload));
    }
}