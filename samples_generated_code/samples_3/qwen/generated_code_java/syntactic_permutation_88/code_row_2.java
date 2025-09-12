import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request req, Response res) -> {
            String yamlPayload = req.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            
            double productPrice = Double.parseDouble(data.get("product_price").toString());
            int quantity = Integer.parseInt(data.get("quantity").toString());

            double totalPrice = productPrice * quantity;
            return String.valueOf(totalPrice);
        });
    }
}