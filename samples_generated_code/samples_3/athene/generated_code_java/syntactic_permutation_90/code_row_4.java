import java.io.ByteArrayInputStream;
import java.io.IOException;
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

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response calculatePrice(@QueryParam("payload") String payload) {
        Map<String, Object> yamlMap = new HashMap<>();
        try (ByteArrayInputStream input = new ByteArrayInputStream(payload.getBytes())) {
            Yaml yaml = new Yaml();
            yamlMap = yaml.load(input);
        } catch (IOException e) {
            return Response.status(Response.Status.BAD_REQUEST).entity("Invalid YAML payload").build();
        }

        String productCode = (String) yamlMap.get("product_code");
        Integer quantity = (Integer) yamlMap.get("quantity");

        if (productCode == null || quantity == null) {
            return Response.status(Response.Status.BAD_REQUEST).entity("Missing product_code or quantity").build();
        }

        double totalPrice = get_price_for_product_code(productCode) * quantity;

        Map<String, Object> result = new HashMap<>();
        result.put("total_price", totalPrice);

        Yaml outputYaml = new Yaml();
        String yamlResult = outputYaml.dump(result);

        return Response.ok(yamlResult).build();
    }

    private double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            case "C789":
                return 5.25;
            default:
                return 0.0;
        }
    }
}