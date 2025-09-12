import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import io.javalin.Javalin;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        // Initialize with some sample products and prices
        productPrices.put("A", 2.50);
        productPrices.put("B", 3.00);
        productPrices.put("C", 4.75);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/calculate-price", ctx -> {
            String yamlPayload = ctx.queryParam("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                ctx.status(400).result("{\"error\": \"Missing payload\"}");
                return;
            }

            ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
            Map<String, Object> inputMap;

            try {
                inputMap = mapper.readValue(yamlPayload, HashMap.class);
            } catch (Exception e) {
                ctx.status(400).result("{\"error\": \"Invalid YAML format\"}");
                return;
            }

            String productCode = (String) inputMap.get("product_code");
            Integer quantity = (Integer) inputMap.get("quantity");

            if (productCode == null || quantity == null || quantity <= 0) {
                ctx.status(400).result("{\"error\": \"Invalid product code or quantity\"}");
                return;
            }

            double price = get_price_for_product_code(productCode);
            double totalPrice = price * quantity;

            Map<String, Double> outputMap = new HashMap<>();
            outputMap.put("total_price", totalPrice);

            try {
                ctx.result(mapper.writeValueAsString(outputMap));
            } catch (Exception e) {
                ctx.status(500).result("{\"error\": \"Internal server error\"}");
            }
        });
    }
}