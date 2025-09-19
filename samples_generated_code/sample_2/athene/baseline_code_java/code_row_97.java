import java.util.Map;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import org.yaml.snakeyaml.Yaml;

@Path("/calculate_price")
public class PriceCalculator {

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public Response calculatePrice(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(payload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = getPriceForProductCode(productCode);
        double totalPrice = price * quantity;

        return Response.ok(String.valueOf(totalPrice)).build();
    }

    private double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            case "C789":
                return 5.25;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}