import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class ProductService {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.post("/calculate_price", (request, response) -> {
            try {
                String yamlPayload = request.queryParams("payload");
                Yaml yaml = new Yaml();
                Map<String, Object> dataMap = yaml.load(yamlPayload);

                String productCode = (String) dataMap.get("product_code");
                int quantity = ((Number) dataMap.get("quantity")).intValue();

                double unitPrice = getUnitPrice(productCode);
                double totalPrice = unitPrice * quantity;

                Map<String, Object> result = new HashMap<>();
                result.put("total_price", totalPrice);

                ObjectMapper mapper = new ObjectMapper();
                String yamlResult = mapper.writeValueAsString(result);

                response.type("application/x-yaml");
                return yamlResult;
            } catch (Exception e) {
                e.printStackTrace();
                response.status(500);
                return "Error processing request";
            }
        });

    }

    private static double getUnitPrice(String productCode) {
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
}