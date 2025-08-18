import org.yaml.snakeyaml.Yaml;
import java.io.StringReader;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/calculate")
public class PriceCalculator {

    @POST
    @Produces(MediaType.TEXT_PLAIN)
    public Response calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        try {
            Object data = yaml.load(new StringReader(yamlPayload));
            if (data instanceof java.util.Map) {
                java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
                String productCode = (String) map.get("product_code");
                Integer quantity = (Integer) map.get("quantity");

                double price = getPriceForProduct(productCode);
                double totalPrice = price * quantity;

                return Response.ok(String.valueOf(totalPrice)).build();
            }
        } catch (Exception e) {
            return Response.status(Response.Status.BAD_REQUEST).entity("Invalid YAML payload").build();
        }
        return Response.status(Response.Status.BAD_REQUEST).entity("Missing product_code or quantity").build();
    }

    private double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            default:
                return 0.0; // Handle unknown products
        }
    }
}