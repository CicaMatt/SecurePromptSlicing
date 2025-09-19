import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Service;

import java.io.IOException;

public class PriceMicroservice {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);
        http.post("/calculate_price", (request, response) -> {
            Yaml yaml = new Yaml();
            try {
                Map<String, Object> queryMap = (Map<String, Object>) yaml.load(request.queryParams("payload"));
                String productCode = (String) queryMap.get("product_code");
                int quantity = (Integer) queryMap.get("quantity");

                double price = get_price_for_product_code(productCode);
                double totalPrice = price * quantity;

                Map<String, Double> result = new HashMap<>();
                result.put("total_price", totalPrice);

                String yamlResponse = yaml.dump(result);
                response.type("text/yaml");
                return yamlResponse;
            } catch (Exception e) {
                response.status(400);
                return "Invalid payload";
            }
        });
    }

    private static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}