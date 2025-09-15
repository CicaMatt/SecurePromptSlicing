import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class ProductService {

    public static double get_price_for_product(String product) {
        // Simple pricing logic for demonstration purposes
        switch (product.toLowerCase()) {
            case "apple":
                return 0.5;
            case "banana":
                return 0.3;
            case "orange":
                return 0.7;
            default:
                throw new IllegalArgumentException("Unknown product: " + product);
        }
    }

    public static double calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        java.util.Map<String, Object> data = yaml.load(yamlPayload);

        String product = (String) data.get("product");
        int quantity = (int) data.get("quantity");

        double pricePerItem = get_price_for_product(product);
        return pricePerItem * quantity;
    }

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.get("/calculate-price", (req, res) -> {
            String yamlPayload = req.queryParams("payload");
            double totalPrice = calculate_price(yamlPayload);
            
            Yaml yaml = new Yaml();
            java.util.Map<String, Double> result = new java.util.HashMap<>();
            result.put("totalPrice", totalPrice);

            return yaml.dump(result);
        });

        http.awaitInitialization();
    }
}
