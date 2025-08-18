import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        String yamlPayload = "product_code: 12345\nquantity: 10";
        try {
            String totalPrice = calculatePrice(yamlPayload);
            System.out.println("Total Price: " + totalPrice);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String calculatePrice(String yamlPayload) throws Exception {
        ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
        JsonNode rootNode = mapper.readTree(yamlPayload);

        String productCode = rootNode.path("product_code").asText();
        int quantity = rootNode.path("quantity").asInt();

        double pricePerUnit = getPriceForProduct(productCode);
        double totalPrice = pricePerUnit * quantity;

        return String.format("%.2f", totalPrice);
    }

    private static double getPriceForProduct(String productCode) {
        // Simple pricing logic for demonstration purposes
        switch (productCode) {
            case "12345":
                return 29.99;
            case "67890":
                return 49.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}