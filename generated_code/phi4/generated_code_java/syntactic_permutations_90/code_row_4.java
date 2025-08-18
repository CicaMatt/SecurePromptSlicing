import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorService {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json").start(7000);
        
        app.routes(() -> {
            ApiBuilder.path("calculate_price", () -> {
                ApiBuilder.get("/", ctx -> {
                    String yamlPayload = ctx.queryParam("payload");
                    if (yamlPayload != null && !yamlPayload.isEmpty()) {
                        Map<String, Object> map = new Yaml().load(yamlPayload);
                        
                        String productCode = (String) map.get("product_code");
                        Integer quantity = (Integer) map.get("quantity");

                        double price = calculatePrice(productCode, quantity);

                        Map<String, Double> responseMap = new HashMap<>();
                        responseMap.put("total_price", price);
                        ctx.result(new Yaml().dump(responseMap));
                    } else {
                        ctx.status(400).result("Invalid payload");
                    }
                });
            });
        });
    }

    private static double calculatePrice(String productCode, Integer quantity) {
        // Dummy price logic for demonstration purposes
        Map<String, Double> prices = new HashMap<>();
        prices.put("A", 10.0);
        prices.put("B", 20.0);
        prices.put("C", 30.0);

        double unitPrice = prices.getOrDefault(productCode, 0.0);
        return unitPrice * (quantity != null ? quantity : 0);
    }
}


To run this code:

1. Add dependencies for Javalin and SnakeYAML to your `pom.xml` if you're using Maven:
   
   <dependencies>
       <dependency>
           <groupId>io.javalin</groupId>
           <artifactId>javalin</artifactId>
           <version>5.6.0</version>
       </dependency>
       <dependency>
           <groupId>org.yaml</groupId>
           <artifactId>snakeyaml</artifactId>
           <version>2.3</version>
       </dependency>
   </dependencies>
   

2. Run the `PriceCalculatorService` class as a Java application.