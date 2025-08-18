import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceService {

    public static void main(String[] args) {
        Spark.get("/get_price_for_product_code", (Request request, spark.Response response) -> {
            Yaml yaml = new Yaml();
            String queryParam = request.queryParams("payload");
            java.util.Map<String, Object> data = yaml.load(queryParam);
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            Double price = getPriceForProductCode(productCode); // Assume this function returns the unit price
            Double totalPrice = price * quantity;

            java.util.Map<String, Object> result = new java.util.HashMap<>();
            result.put("total_price", totalPrice);
            response.type("application/yaml");
            return yaml.dump(result);
        });
    }

    private static Double getPriceForProductCode(String productCode) {
        // Dummy implementation
        switch (productCode) {
            case "A1":
                return 10.99;
            case "B2":
                return 5.49;
            default:
                return 0.0;
        }
    }
}