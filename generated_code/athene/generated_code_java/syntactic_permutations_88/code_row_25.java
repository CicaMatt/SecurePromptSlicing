import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 5";
        String price = calculate_price(yamlPayload);
        System.out.println(price);
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (int) (long) data.get("quantity");

        double price = getPriceForProduct(productCode) * quantity;
        return Double.toString(price);
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            default:
                return 0.0;
        }
    }
}