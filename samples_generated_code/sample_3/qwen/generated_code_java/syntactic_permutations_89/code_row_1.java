import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/calculatePrice", (Request request, Response response) -> {
            String productCode = request.queryParams("productCode");
            int quantity = Integer.parseInt(request.queryParams("quantity"));
            double price = calculatePrice(productCode, quantity);
            return String.valueOf(price);
        });
    }

    public static double calculatePrice(String productCode, int quantity) {
        double basePrice;
        switch (productCode) {
            case "A001":
                basePrice = 19.99;
                break;
            case "B002":
                basePrice = 29.99;
                break;
            case "C003":
                basePrice = 49.99;
                break;
            default:
                return -1; // Invalid product code
        }
        return basePrice * quantity;
    }
}