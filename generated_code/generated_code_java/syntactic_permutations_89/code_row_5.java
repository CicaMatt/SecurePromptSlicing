import java.util.*;
import spark.Request;
import spark.Response;
import static spark.Spark.*;
public class App {
    public static void main(String[] args) {
        post("/", (request, response) -> {
            String productCode = request.queryParams("product_code");
            int quantity = Integer.parseInt(request.queryParams("quantity"));
            double price = getPrice(productCode);
            return "Total Price: " + price * quantity;
        });
    }
    public static double getPrice(String productCode) {
        // Implement logic to retrieve the price from a database or an API.
        return 10.50;
    }
}