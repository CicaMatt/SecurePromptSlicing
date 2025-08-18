import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorApi {

    static {
        // Mock database of products and their prices
        ProductDatabase.init();
    }

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = Integer.parseInt(data.get("quantity").toString());

            double price = ProductDatabase.getPrice(productCode);
            double totalPrice = price * quantity;

            return Double.toString(totalPrice);
        });
    }
}

class ProductDatabase {
    private static java.util.Map<String, Double> products;

    public static void init() {
        products = new java.util.HashMap<>();
        products.put("A123", 19.99);
        products.put("B456", 29.99);
        products.put("C789", 9.99);
    }

    public static double getPrice(String productCode) {
        return products.getOrDefault(productCode, 0.0);
    }
}