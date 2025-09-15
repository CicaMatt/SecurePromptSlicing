import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/calculate-price", (Request req, Response res) -> {
            String quantityParam = req.queryParams("quantity");
            int quantity = quantityParam != null ? Integer.parseInt(quantityParam) : 0;
            double pricePerUnit = getPricePerUnit();
            double totalPrice = calculateTotalPrice(pricePerUnit, quantity);
            return String.valueOf(totalPrice);
        });
    }

    private static double getPricePerUnit() {
        return 19.99; // Example price per unit
    }

    private static double calculateTotalPrice(double pricePerUnit, int quantity) {
        return pricePerUnit * quantity;
    }
}
