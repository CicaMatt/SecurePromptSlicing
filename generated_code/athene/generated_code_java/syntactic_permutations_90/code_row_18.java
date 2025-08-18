import java.util.HashMap;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import org.yaml.snakeyaml.Yaml;

@Path("/calculatePrice")
public class PriceCalculatorService {

    private HashMap<String, Double> productPrices = new HashMap<>();

    public PriceCalculatorService() {
        productPrices.put("A123", 10.5);
        productPrices.put("B456", 20.0);
        productPrices.put("C789", 15.25);
    }

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String calculate_price(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        HashMap<String, Object> data = (HashMap<String, Object>) yaml.load(payload);

        String productCode = (String) data.get("product_code");
        int quantity = (int) ((Double) data.get("quantity")).doubleValue();

        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;

        HashMap<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        return yaml.dump(result);
    }

    private double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}