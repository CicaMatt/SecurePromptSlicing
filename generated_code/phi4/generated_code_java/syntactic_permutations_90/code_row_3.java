import io.javalin.Javalin;
import io.javalin.http.Context;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        app.post("/calculate_price", ProductService::calculatePrice);
    }

    private static double get_price_for_product_code(String productCode) {
        // Simple mock implementation
        Map<String, Double> priceMap = Map.of(
            "P001", 10.99,
            "P002", 15.50,
            "P003", 7.75
        );
        return priceMap.getOrDefault(productCode, 0.0);
    }

    private static void calculatePrice(Context ctx) {
        String yamlQuery = ctx.queryParam("payload");
        
        if (yamlQuery == null || yamlQuery.isEmpty()) {
            ctx.status(400).result("Payload is required.");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> payloadMap = yaml.load(yamlQuery);

        String productCode = (String) payloadMap.get("product_code");
        Integer quantity = (Integer) payloadMap.get("quantity");

        if (productCode == null || quantity == null) {
            ctx.status(400).result("Invalid payload format.");
            return;
        }

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> responseMap = Map.of(
            "total_price", totalPrice
        );

        String resultYaml = yaml.dump(responseMap);

        ctx.result(resultYaml);
    }
}


Make sure to include the following dependencies in your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.8.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.30</version>
    </dependency>
</dependencies>