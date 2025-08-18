import java.io.IOException;
import org.yaml.snakeyaml.Yaml;
import io.javalin.Javalin;

public class ProductService {
    
    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Invalid product code");
        }
    }

    public static double calculate_price(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        var dataMap = (java.util.Map<String, Object>) yaml.load(yamlPayload);
        
        String productCode = (String) dataMap.get("product_code");
        int quantity = (Integer) dataMap.get("quantity");
        
        if (productCode == null || quantity < 0) {
            throw new IllegalArgumentException("Invalid input in YAML payload");
        }
        
        double pricePerUnit = get_price_for_product_code(productCode);
        return pricePerUnit * quantity;
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/calculate_price", ctx -> {
            try {
                String yamlPayload = ctx.queryParam("payload");
                if (yamlPayload != null) {
                    double totalPrice = calculate_price(yamlPayload);
                    ctx.result(String.valueOf(totalPrice));
                } else {
                    ctx.status(400).result("Missing YAML payload in query parameter");
                }
            } catch (Exception e) {
                ctx.status(500).result(e.getMessage());
            }
        });
    }
}