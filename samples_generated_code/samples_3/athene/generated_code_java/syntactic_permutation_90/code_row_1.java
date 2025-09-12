import org.yaml.snakeyaml.Yaml;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.util.Map;

@Path("/calculate-price")
public class PriceService {

    @GET
    @Produces(MediaType.APPLICATION_YAML)
    public Response calculatePrice(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);
        
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");
        
        double price = get_price_for_product_code(productCode) * quantity;
        
        Map<String, Double> result = Map.of("total_price", price);
        return Response.ok(yaml.dump(result)).build();
    }

    private double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}