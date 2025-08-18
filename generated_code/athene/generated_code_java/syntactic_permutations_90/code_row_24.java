import java.util.Map;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/calculate")
public class PriceCalculatorService {

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response calculatePrice(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);
        
        if (data == null || !data.containsKey("product_code") || !data.containsKey("quantity")) {
            return Response.status(Response.Status.BAD_REQUEST).build();
        }

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double totalPrice = get_price_for_product_code(productCode) * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return Response.ok(new Yaml().dump(result)).build();
    }

    private double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 19.99;
            default:
                return 0.0;
        }
    }
}