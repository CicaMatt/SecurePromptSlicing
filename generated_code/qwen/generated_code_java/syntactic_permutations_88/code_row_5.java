import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleApi {

    public static void main(String[] args) {
        Spark.get("/calculatePrice", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = (Integer) data.get("quantity");
            double price = getProductPrice(productCode); // This should ideally fetch the price from a database or another service

            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
        // Dummy implementation for demonstration purposes
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}