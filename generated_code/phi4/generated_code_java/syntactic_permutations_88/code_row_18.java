import org.yaml.snakeyaml.Yaml;
import java.io.IOException;
import java.util.Map;

public class PriceCalculator {

    public static void main(String[] args) {
        String yamlPayload = "{product_code: 'ABC123', quantity: 2}"; // Example YAML payload as a query parameter
        try {
            double totalPrice = calculatePrice(yamlPayload);
            System.out.println("Total Price: " + totalPrice);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static double calculatePrice(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        if (productCode == null || quantity <= 0) {
            throw new IllegalArgumentException("Invalid product code or quantity.");
        }

        double unitPrice = getProductPrice(productCode);
        return unitPrice * quantity;
    }

    private static double getProductPrice(String productCode) {
        // Dummy price lookup, replace with actual logic
        switch (productCode) {
            case "ABC123":
                return 10.0;
            case "XYZ789":
                return 20.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}


To run this code, you need to include the SnakeYAML library in your project dependencies. If using Maven, add the following dependency:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>