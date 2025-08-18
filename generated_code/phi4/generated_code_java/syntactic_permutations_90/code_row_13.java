import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;
import java.io.InputStream;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/calculate_price", ctx -> {
            String yamlData = ctx.queryParam("data");
            if (yamlData == null || yamlData.isEmpty()) {
                ctx.result("Invalid input: 'data' query parameter is required.");
                return;
            }
            
            Yaml yaml = new Yaml();
            Object data = yaml.load(yamlData);
            if (data instanceof java.util.Map) {
                java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                String productCode = (String) map.get("product_code");
                Integer quantity = (Integer) map.get("quantity");

                if (productCode == null || quantity == null) {
                    ctx.result("Invalid input: 'product_code' and 'quantity' are required in the YAML payload.");
                    return;
                }

                Double price = get_price_for_product_code(productCode);
                if (price != null) {
                    double totalPrice = price * quantity;
                    ctx.result(String.valueOf(totalPrice));
                } else {
                    ctx.status(404).result("Product code not found");
                }
            } else {
                ctx.result("Invalid input: YAML payload must contain a map.");
            }
        });
    }

    public static Double get_price_for_product_code(String productCode) {
        // Example hardcoded product prices
        switch (productCode.toLowerCase()) {
            case "abc123":
                return 10.0;
            case "xyz789":
                return 20.5;
            default:
                return null;
        }
    }
}


Make sure to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.8.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>