import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class PriceCalculator {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Object data = yaml.load(yamlPayload);
            // Assuming the payload contains a 'price' field for demonstration
            double price = ((Number) ((java.util.Map) data).get("price")).doubleValue();
            return String.valueOf(price * 1.2); // Example calculation: adding 20% to the price
        });
    }
}
