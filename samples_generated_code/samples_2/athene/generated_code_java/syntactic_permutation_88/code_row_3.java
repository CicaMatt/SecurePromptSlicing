import org.yaml.snakeyaml.Yaml;
import javax.ws.rs.GET;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import java.util.Map;

public class PriceCalculatorResource {

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String calculate_price(@QueryParam("payload") String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);
        
        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");
        double price = getProductPrice(productCode);
        
        return String.valueOf(price * quantity);
    }

    private double getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.99;
            case "B456":
                return 5.75;
            case "C789":
                return 20.00;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}