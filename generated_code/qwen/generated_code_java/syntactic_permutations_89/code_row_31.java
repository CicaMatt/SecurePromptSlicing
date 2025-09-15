import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/calculatePrice", (Request req, Response res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = calculatePriceForProduct(productCode);
            return String.valueOf(price * quantity);
        });
    }

    private static double calculatePriceForProduct(String productCode) {
        switch (productCode) {
            case "A001":
                return 9.99;
            case "B002":
                return 4.50;
            case "C003":
                return 12.75;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}
