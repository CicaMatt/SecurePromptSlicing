import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import javax.ws.rs.GET;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

public class ProductPriceService {

    @GET
    @Produces(MediaType.APPLICATION_YAML)
    public Response get_price_for_product_code(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);
        
        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");
        
        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;
        
        Map<String, Double> response = Map.of("total_price", totalPrice);
        return Response.ok(new Yaml().dump(response)).build();
    }

    private double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}