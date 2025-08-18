import java.util.Map;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.get;

public class PriceCalculatorService {

    private Map<String, Double> productPrices = new HashMap<>();

    public PriceCalculatorService() {
        productPrices.put("A123", 10.5);
        productPrices.put("B456", 20.0);
        productPrices.put("C789", 15.0);
    }

    private double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public String calculate_price(Request request, Response response) {
        String yamlPayload = request.queryParams("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);

        double totalPrice = 0.0;
        for (String productCode : (Iterable<String>) data.get("products")) {
            totalPrice += get_price_for_product_code(productCode);
        }

        Map<String, Double> result = new HashMap<>();
        result.put("totalPrice", totalPrice);
        return yaml.dump(result);
    }

    public static void main(String[] args) {
        PriceCalculatorService service = new PriceCalculatorService();
        get("/calculate-price", service::calculate_price);
    }
}