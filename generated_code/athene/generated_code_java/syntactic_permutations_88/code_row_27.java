import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        double totalPrice = calculatePrice(yamlPayload);
        System.out.println(totalPrice);
    }

    public static double calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = getProductPrice(productCode);
        return pricePerUnit * quantity;
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.50;
            case "B456":
                return 20.75;
            case "C789":
                return 15.00;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}