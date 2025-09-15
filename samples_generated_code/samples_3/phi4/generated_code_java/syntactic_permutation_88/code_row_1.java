import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

import java.util.Map;

public class PriceCalculatorAPI {
    public static void main(String[] args) {
        post("/calculate_price", (request, response) -> {
            response.type("text/plain");
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                return "Error: Missing payload";
            }
            
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            Integer price = (Integer) data.get("price");
            Integer quantity = (Integer) data.get("quantity");

            if (price == null || quantity == null) {
                return "Error: Invalid payload";
            }

            int totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }
}
