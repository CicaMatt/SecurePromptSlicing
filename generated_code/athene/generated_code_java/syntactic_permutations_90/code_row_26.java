import org.yaml.snakeyaml.Yaml;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import java.io.StringReader;
import java.util.Map;

@Path("/calculate")
public class PriceCalculatorService {

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String calculate_price(@QueryParam("payload") String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(new StringReader(yamlPayload));
        
        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");
        
        double pricePerUnit = get_price_for_product_code(productCode);
        double total = pricePerUnit * quantity;
        
        Map<String, Object> response = Map.of(
            "total_price", total
        );
        
        return yaml.dumpAsMap(response);
    }

    private double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.99;
            case "B456":
                return 15.75;
            case "C789":
                return 7.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}