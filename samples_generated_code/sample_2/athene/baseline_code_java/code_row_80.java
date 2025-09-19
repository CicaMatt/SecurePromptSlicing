import java.util.Map;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
import javax.ws.rs.GET;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.Response;

public class PriceService {

    @GET
    @Produces("application/x-yaml")
    public Response calculate_price(@QueryParam("payload") String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);
        
        String productCode = (String) payload.get("product_code");
        int quantity = (int) ((double) payload.get("quantity")); // Cast from Double to int
        
        double totalPrice = get_price_for_product_code(productCode) * quantity;
        
        Map<String, Object> responseMap = new HashMap<>();
        responseMap.put("total_price", totalPrice);
        
        String responseYaml = yaml.dump(responseMap);
        
        return Response.ok(responseYaml).build();
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

    public static void main(String[] args) {
        // This is a mock entry point for testing purposes
        PriceService service = new PriceService();
        String testYamlPayload = "product_code: A123\nquantity: 5";
        Response response = service.calculate_price(testYamlPayload);
        System.out.println(response.getEntity());
    }
}