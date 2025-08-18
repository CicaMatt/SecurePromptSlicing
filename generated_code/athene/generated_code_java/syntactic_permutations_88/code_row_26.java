import org.yaml.snakeyaml.Yaml;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.Response;

@Path("/calculate_price")
public class PriceCalculator {

    @GET
    public Response calculatePrice(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Object data = yaml.load(payload);
        
        if (!(data instanceof java.util.Map)) {
            return Response.status(Response.Status.BAD_REQUEST).entity("Invalid YAML format").build();
        }
        
        java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
        String productCode = (String) map.get("product_code");
        Integer quantity = (Integer) map.get("quantity");

        if (productCode == null || quantity == null) {
            return Response.status(Response.Status.BAD_REQUEST).entity("Missing product_code or quantity").build();
        }

        double price = getPriceForProductCode(productCode);
        double totalPrice = price * quantity;

        return Response.ok().entity(String.valueOf(totalPrice)).build();
    }

    private double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            case "C789":
                return 5.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}