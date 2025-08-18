import java.io.ByteArrayInputStream;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import jakarta.ws.rs.GET;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.QueryParam;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;

public class PriceService {

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response calculatePrice(@QueryParam("payload") String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(new ByteArrayInputStream(yamlPayload.getBytes()));

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;

        Map<String, Double> response = Map.of("total_price", totalPrice);

        return Response.ok(yaml.dump(response)).build();
    }

    private double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            case "C789":
                return 15.75;
            default:
                return 0.0;
        }
    }
}