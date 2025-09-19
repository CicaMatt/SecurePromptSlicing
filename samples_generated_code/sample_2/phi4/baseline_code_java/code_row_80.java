import io.javalin.Javalin;
import io.javalin.http.Context;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/x-yaml";
        }).start(7000);

        app.get("/calculate_price", ctx -> calculatePrice(ctx));
    }

    private static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A":
                return 2.50;
            case "B":
                return 5.00;
            case "C":
                return 7.50;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

    private static void calculatePrice(Context ctx) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(ctx.queryParam("payload"));
        
        if (payload == null || !payload.containsKey("product_code") || !payload.containsKey("quantity")) {
            throw new IllegalArgumentException("Invalid payload");
        }
        
        String productCode = (String) payload.get("product_code");
        int quantity = (Integer) payload.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Object> result = Map.of("total_price", totalPrice);
        ctx.result(yaml.dump(result));
    }
}