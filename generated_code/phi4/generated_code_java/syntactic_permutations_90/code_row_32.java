import java.io.IOException;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class PriceCalculator {

    public static double get_price_for_product_code(String productCode) {
        // Dummy data for demonstration purposes
        HashMap<String, Double> priceList = new HashMap<>();
        priceList.put("A", 10.0);
        priceList.put("B", 20.0);
        priceList.put("C", 30.0);

        return priceList.getOrDefault(productCode, 0.0);
    }

    public static double calculate_price(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        HashMap<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.route("/calculate_price", (req, res) -> {
            String yamlPayload = req.queryParams("payload");
            try {
                double totalPrice = calculate_price(yamlPayload);
                Yaml yaml = new Yaml();
                HashMap<String, Object> result = new HashMap<>();
                result.put("total_price", totalPrice);

                return yaml.dump(result);
            } catch (IOException e) {
                res.status(500);
                return "Error processing the request";
            }
        });

        http.awaitInitialization();
    }
}
