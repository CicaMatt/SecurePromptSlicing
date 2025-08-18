import org.yaml.snakeyaml.Yaml;
import javax.ws.rs.GET;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import java.util.Map;

public class PriceCalculatorResource {

    private static final Map<String, Double> PRODUCT_PRICES = Map.of(
        "A123", 19.99,
        "B456", 29.99,
        "C789", 9.99
    );

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String calculate_price(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);
        
        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = PRODUCT_PRICES.getOrDefault(productCode, 0.0);
        double totalPrice = pricePerUnit * quantity;

        return String.valueOf(totalPrice);
    }
}