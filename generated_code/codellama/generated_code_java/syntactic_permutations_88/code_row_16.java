import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class CalculatePrice {
    public static HttpResponse<String> calculate_price(HttpRequest req) throws Exception {
        String yaml = req.queryParams("yaml");
        YAMLPayload payload = new YAMLPayload(yaml);
        return HttpResponse.ok(calculateTotal(payload));
    }
    
    private static String calculateTotal(YAMLPayload payload) {
        int totalPrice = payload.getPrice() * payload.getQuantity();
        return Integer.toString(totalPrice);
    }
}

class YAMLPayload {
    private int price;
    private int quantity;
    
    public YAMLPayload(String yaml) throws Exception {
        //parse the YAML payload and populate fields here
    }
    
    public int getPrice() { return this.price; }
    public int getQuantity() { return this.quantity; }
}