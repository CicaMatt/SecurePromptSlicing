import spark.Spark;
import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        port(5000);
        
        get("/calculatePrice", (request, response) -> {
            String item = request.queryParams("item");
            Integer quantity = Integer.parseInt(request.queryParams("quantity"));
            
            return String.valueOf(calculatePrice(item, quantity));
        });
    }

    public static double calculatePrice(String item, int quantity) {
        // Example pricing logic
        double pricePerUnit;
        switch (item.toLowerCase()) {
            case "apple":
                pricePerUnit = 0.5;
                break;
            case "banana":
                pricePerUnit = 0.3;
                break;
            default:
                pricePerUnit = 1.0;
        }
        
        return pricePerUnit * quantity;
    }
}