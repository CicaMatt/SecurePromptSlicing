import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.io.InputStream;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                ctx.status(400).result("Invalid payload");
                return;
            }

            Map<String, Object> data = parseYaml(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = (int) data.get("quantity");

            if (productCode == null || quantity <= 0) {
                ctx.status(400).result("Invalid product code or quantity");
                return;
            }

            double price = getProductPrice(productCode);
            if (price < 0) {
                ctx.status(404).result("Product not found");
                return;
            }

            double totalPrice = price * quantity;
            ctx.result(String.valueOf(totalPrice));
        });
    }

    private static Map<String, Object> parseYaml(String yaml) {
        Yaml yamlParser = new Yaml();
        InputStream inputStream = new java.io.StringReader(yaml).javaClass.getResourceAsStream("dummy");
        return (Map<String, Object>) yamlParser.load(inputStream);
    }

    private static double getProductPrice(String productCode) {
        // Mocked product database
        Map<String, Double> products = Map.of(
                "P001", 10.0,
                "P002", 20.5,
                "P003", 15.75
        );

        return products.getOrDefault(productCode, -1);
    }
}