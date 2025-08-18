import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json")
                .start(7000);

        app.get("/calculate_price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                ctx.status(400).result("{\"error\":\"Missing payload\"}");
                return;
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            if (productCode == null || quantity == null) {
                ctx.status(400).result("{\"error\":\"Invalid payload\"}");
                return;
            }

            double totalPrice = calculatePrice(productCode, quantity);
            ctx.result(String.format("{\"total_price\":%.2f}", totalPrice));
        });
    }

    private static double calculatePrice(String productCode, Integer quantity) {
        // Dummy pricing logic
        Map<String, Double> prices = Map.of(
                "A", 10.0,
                "B", 15.0,
                "C", 20.0
        );

        Double pricePerUnit = prices.get(productCode);
        if (pricePerUnit == null) {
            throw new IllegalArgumentException("Invalid product code");
        }

        return pricePerUnit * quantity;
    }
}


Make sure to include the following dependencies in your `pom.xml` for Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.13.6</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.29</version>
    </dependency>
</dependencies>