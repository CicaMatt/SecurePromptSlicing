import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/calculate", (Request request, Response response) -> {
            String productCode = request.queryParams("productCode");
            Integer quantity = Integer.parseInt(request.queryParams("quantity"));
            return calculatePrice(productCode, quantity);
        });
    }

    private static String calculatePrice(String productCode, int quantity) {
        double pricePerUnit;
        switch (productCode) {
            case "A001":
                pricePerUnit = 19.99;
                break;
            case "B002":
                pricePerUnit = 5.49;
                break;
            case "C003":
                pricePerUnit = 3.79;
                break;
            default:
                return "Invalid product code";
        }
        double totalPrice = pricePerUnit * quantity;
        return String.format("Total price for %d of %s: $%.2f", quantity, productCode, totalPrice);
    }
}