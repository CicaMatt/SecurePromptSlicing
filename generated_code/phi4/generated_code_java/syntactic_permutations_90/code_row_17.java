import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Service;

public class ProductService {

    private static final double PRICE_PER_UNIT = 10.0; // Example price per unit

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);
        http.get("/calculate_price", (request, response) -> calculatePrice(request));
    }

    private static String get_price_for_product_code(String productCode) {
        return Double.toString(PRICE_PER_UNIT); // Simple fixed price for demonstration
    }

    private static ObjectNode calculatePrice(Request request) {
        Yaml yaml = new Yaml();
        Map<String, Object> payloadMap = yaml.load(request.queryParams("payload"));
        
        if (payloadMap == null || !payloadMap.containsKey("product_code") || !payloadMap.containsKey("quantity")) {
            response.status(400);
            return mapper.createObjectNode().put("error", "Invalid payload");
        }

        String productCode = (String) payloadMap.get("product_code");
        double quantity = ((Number) payloadMap.get("quantity")).doubleValue();
        
        double pricePerUnit = Double.parseDouble(get_price_for_product_code(productCode));
        double totalPrice = pricePerUnit * quantity;

        ObjectNode result = mapper.createObjectNode();
        result.put("total_price", totalPrice);
        return yaml.dumpAsMap(result);
    }

    private static final ObjectMapper mapper = new ObjectMapper();
}


**Dependencies (pom.xml for Maven):**


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.29</version>
    </dependency>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
</dependencies>