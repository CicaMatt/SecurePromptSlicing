import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/price/:productCode/:quantity", (Request request, Response response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double price = calculatePrice(productCode, quantity);
            return Double.toString(price);
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        // Example pricing logic
        switch (productCode) {
            case "A1":
                return 10.99 * quantity;
            case "B2":
                return 5.49 * quantity;
            case "C3":
                return 7.89 * quantity;
            default:
                return -1; // Product not found
        }
    }
}
