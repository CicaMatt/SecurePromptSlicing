import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculator {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = (Integer) data.get("quantity");

            double price = getProductPrice(productCode); // This should ideally fetch the price from a database or another service
            double totalPrice = price * quantity;

            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A001":
                return 9.99;
            case "B002":
                return 14.50;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}