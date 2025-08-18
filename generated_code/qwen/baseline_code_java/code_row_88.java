import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;

            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A001":
                return 19.99;
            case "B002":
                return 5.49;
            case "C003":
                return 3.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}