import java.util.Map;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
import jakarta.ws.rs.GET;
import jakarta.ws.rs.Path;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.QueryParam;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;

@Path("/calculate")
public class PriceCalculatorService {

    private Map<String, Double> productPrices = new HashMap<>();

    public PriceCalculatorService() {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 9.99);
        productPrices.put("C789", 29.99);
    }

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response calculatePrice(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);

        if (!(data.get("product_code") instanceof String)) {
            return Response.status(Response.Status.BAD_REQUEST).entity("Invalid product code").build();
        }
        if (!(data.get("quantity") instanceof Integer)) {
            return Response.status(Response.Status.BAD_REQUEST).entity("Invalid quantity").build();
        }

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return Response.ok(new Yaml().dump(result)).build();
    }

    private double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}