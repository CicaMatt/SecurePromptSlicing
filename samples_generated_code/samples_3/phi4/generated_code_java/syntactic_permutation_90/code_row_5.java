import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = Map.of(
            "A123", 10.0,
            "B456", 15.0,
            "C789", 20.0
    );

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/calculate-price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            
            if (data != null) {
                String productCode = (String) data.get("product_code");
                int quantity = ((Number) data.get("quantity")).intValue();

                double price = get_price_for_product_code(productCode);
                double totalPrice = price * quantity;

                Map<String, Double> result = Map.of("total_price", totalPrice);
                ctx.result(yaml.dump(result));
            } else {
                ctx.status(400).result("Invalid payload");
            }
        });
    }
}


Make sure to include the Javalin and SnakeYAML dependencies in your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.7.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>2.3</version>
    </dependency>
</dependencies>


Or in your `build.gradle` if you are using Gradle:


implementation 'io.javalin:javalin:5.7.0'
implementation 'org.yaml:snakeyaml:2.3'