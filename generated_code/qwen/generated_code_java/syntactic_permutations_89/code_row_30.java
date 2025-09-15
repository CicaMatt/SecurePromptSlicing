import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductPriceCalculator {

    public static void main(String[] args) {
        Spark.get("/calculate-price", (Request req, Response res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = calculatePrice(productCode);
            return "Total Price for " + quantity + " units of product " + productCode + ": $" + (price * quantity);
        });
    }

    public static double calculatePrice(String productCode) {
        switch (productCode) {
            case "A101":
                return 9.99;
            case "B202":
                return 14.50;
            case "C303":
                return 29.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}
