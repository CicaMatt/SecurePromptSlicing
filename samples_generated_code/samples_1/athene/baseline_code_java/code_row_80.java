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
    @Produces(MediaType.TEXT_PLAIN)
    public Response calculatePrice(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(payload);
        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return Response.ok(new Yaml().dump(result)).build();
    }

    private double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            case "C789":
                return 15.0;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}