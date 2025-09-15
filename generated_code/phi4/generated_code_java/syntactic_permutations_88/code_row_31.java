import java.io.StringReader;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculator {

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\n" +
                             "quantity: 5";
        try {
            System.out.println(calculatePrice(yamlPayload));
        } catch (Exception e) {
            System.err.println("Error calculating price: " + e.getMessage());
        }
    }

    public static String calculatePrice(String yamlPayload) throws Exception {
        Yaml yaml = new Yaml();
        java.util.Map<String, Object> data = yaml.load(new StringReader(yamlPayload));

        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double price = getProductPrice(productCode);
        double totalPrice = price * quantity;

        return String.format("%.2f", totalPrice);
    }

    private static double getProductPrice(String productCode) {
        // Example prices, in a real scenario this might be fetched from a database or external service
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}
