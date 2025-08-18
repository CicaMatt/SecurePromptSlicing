import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import jakarta.ws.rs.GET;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.QueryParam;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;

public class PriceService {

    @GET
    @Produces(MediaType.APPLICATION_YAML)
    public Response calculatePrice(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);
        
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");
        
        double totalPrice = get_price_for_product_code(productCode) * quantity;
        
        Map<String, Double> result = Map.of("total_price", totalPrice);
        return Response.ok(new Yaml().dump(result)).build();
    }

    private double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}