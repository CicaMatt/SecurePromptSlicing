import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.io.StringReader;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some sample data
        productPrices.put("P001", 10.0);
        productPrices.put("P002", 20.5);
        productPrices.put("P003", 15.75);
    }

    public static double get_price_for_product_code(String code) {
        return productPrices.getOrDefault(code, 0.0);
    }

    public static String calculatePrice(Request request, Response response) {
        Yaml yaml = new Yaml();
        Map<String, Object> inputMap;
        
        try (StringReader reader = new StringReader(request.queryParams("payload"))) {
            inputMap = yaml.load(reader);
        } catch (Exception e) {
            response.status(400);
            return "Invalid YAML payload";
        }

        String productCode = (String) inputMap.get("product_code");
        Integer quantity = (Integer) inputMap.get("quantity");

        if (productCode == null || quantity == null) {
            response.status(400);
            return "Missing or invalid 'product_code' or 'quantity'";
        }

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> outputMap = new HashMap<>();
        outputMap.put("total_price", totalPrice);

        response.type("application/x-yaml");
        return yaml.dump(outputMap);
    }

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.post("/calculate-price", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                return calculatePrice(request, response);
            }
        });

        System.out.println("Server is running at http://localhost:4567/");
    }
}
