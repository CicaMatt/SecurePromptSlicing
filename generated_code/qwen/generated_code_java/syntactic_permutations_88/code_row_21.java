import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.InputStream;
import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            InputStream inputStream = yaml.loadAs(yamlPayload.getBytes(), InputStream.class);
            Map<String, Object> data = yaml.load(inputStream);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();
            double price = 10.0; // Assuming a fixed price for demonstration

            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }
}