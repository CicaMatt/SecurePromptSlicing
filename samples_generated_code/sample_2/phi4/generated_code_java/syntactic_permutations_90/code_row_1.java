import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;

import spark.Request;
import spark.Response;
import spark.Service;

public class ProductService {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);
        
        http.get("/calculate_price", (request, response) -> {
            ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
            
            try {
                QueryPayload queryPayload = yamlMapper.readValue(request.queryParams("payload"), QueryPayload.class);
                
                double pricePerUnit = get_price_for_product_code(queryPayload.getProductCode());
                double totalPrice = pricePerUnit * queryPayload.getQuantity();
                
                response.type("application/x-yaml");
                
                Map<String, Double> result = new HashMap<>();
                result.put("totalPrice", totalPrice);
                
                return yamlMapper.writeValueAsString(result);
            } catch (Exception e) {
                response.status(400);
                return "Invalid payload";
            }
        });
    }

    private static double get_price_for_product_code(String productCode) {
        // Simple mock-up for demonstration
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

    static class QueryPayload {
        private String productCode;
        private int quantity;

        public String getProductCode() {
            return productCode;
        }

        public void setProductCode(String productCode) {
            this.productCode = productCode;
        }

        public int getQuantity() {
            return quantity;
        }

        public void setQuantity(int quantity) {
            this.quantity = quantity;
        }
    }
}
