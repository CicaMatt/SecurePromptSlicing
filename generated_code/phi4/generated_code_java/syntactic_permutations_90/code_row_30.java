import org.yaml.snakeyaml.Yaml;
import spark.Service;

import java.io.StringReader;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();
    
    static {
        // Example product codes and prices
        productPrices.put("P001", 10.0);
        productPrices.put("P002", 20.0);
        productPrices.put("P003", 30.0);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
    
    public static void main(String[] args) {
        Service http = Service.ignite().port(8080);

        http.get("/calculate-price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            
            Map<String, Object> inputMap = yaml.load(new StringReader(yamlPayload));
            String productCode = (String) inputMap.get("product_code");
            int quantity = (Integer) inputMap.get("quantity");

            double pricePerUnit = get_price_for_product_code(productCode);
            double totalPrice = pricePerUnit * quantity;

            Map<String, Object> outputMap = new HashMap<>();
            outputMap.put("total_price", totalPrice);

            response.type("application/x-yaml");
            return yaml.dump(outputMap);
        });
    }
}
