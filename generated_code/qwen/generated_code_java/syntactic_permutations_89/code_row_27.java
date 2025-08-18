import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductPriceApp {

    private static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A1":
                return 19.99;
            case "B2":
                return 29.99;
            case "C3":
                return 5.49;
            default:
                return -1.0; // Product not found
        }
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price", (Request request, Response response) -> {
            String productCode = request.queryParams("productCode");
            int quantity = Integer.parseInt(request.queryParamsOrDefault("quantity", "1"));
            double pricePerUnit = getPriceForProductCode(productCode);
            if (pricePerUnit < 0) {
                response.status(404);
                return "Product not found";
            }
            double totalPrice = pricePerUnit * quantity;
            return String.format("%.2f", totalPrice);
        });
    }
}