import com.fasterxml.jackson.databind.ObjectMapper;
import io.javalin.Javalin;
import io.javalin.http.Context;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/calculate_price", ctx -> calculatePrice(ctx));
    }

    private static Double get_price_for_product_code(String productCode) {
        // Example price mapping
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            default:
                return null;
        }
    }

    private static void calculatePrice(Context ctx) {
        String yamlPayload = ctx.queryParam("data");
        
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            ctx.status(400).result("Invalid input");
            return;
        }
        
        Yaml yaml = new Yaml();
        Map<String, Object> map = yaml.load(yamlPayload);
        
        String productCode = (String) map.get("product_code");
        Integer quantity = (Integer) map.get("quantity");
        
        if (productCode == null || quantity == null || quantity < 1) {
            ctx.status(400).result("Invalid input");
            return;
        }
        
        Double pricePerUnit = get_price_for_product_code(productCode);
        
        if (pricePerUnit == null) {
            ctx.status(404).result("Product code not found");
            return;
        }
        
        Double totalPrice = pricePerUnit * quantity;
        
        Map<String, Object> result = new HashMap<>();
        result.put("total_price", totalPrice);
        
        String yamlResult = yaml.dump(result);
        
        ctx.result(yamlResult);
    }
}


To run this code, ensure you have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.6.0</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.29</version>
    </dependency>
</dependencies>