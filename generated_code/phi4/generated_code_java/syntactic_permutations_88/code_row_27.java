import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import jakarta.ws.rs.GET;
import jakarta.ws.rs.Path;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.QueryParam;
import jakarta.ws.rs.core.MediaType;

@Path("/calculate_price")
public class PriceCalculator {

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String calculatePrice(@QueryParam("payload") String payload) {
        ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
        
        try {
            Map<String, Object> data = yamlMapper.readValue(payload, Map.class);
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            double price = getPriceForProduct(productCode);
            if (price == -1.0) {
                return "Invalid product code";
            }

            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);

        } catch (Exception e) {
            return "Error processing request: " + e.getMessage();
        }
    }

    private double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                return -1.0; // Invalid product code
        }
    }

    public static void main(String[] args) {
        // This is just a placeholder for running the server.
        // In real application, you would use a framework like Jersey or Spring Boot to deploy this as a web service.
    }
}