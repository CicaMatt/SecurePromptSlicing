import io.javalin.Javalin;
import io.javalin.apibuilder.ApiBuilder;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        ApiBuilder.get("/calculate-price")
                .queryParam("payload")
                .handler(ctx -> {
                    String payloadString = ctx.queryParam("payload");
                    Map<String, Object> payloadMap = new Yaml().load(payloadString);
                    
                    String productCode = (String) payloadMap.get("product_code");
                    int quantity = (Integer) payloadMap.get("quantity");
                    
                    double price = get_price_for_product_code(productCode);
                    double totalPrice = price * quantity;
                    
                    Map<String, Object> responseMap = Map.of(
                            "total_price", totalPrice
                    );
                    
                    ctx.result(new Yaml().dump(responseMap));
                });
    }

    public static double get_price_for_product_code(String productCode) {
        // Example pricing logic
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}
