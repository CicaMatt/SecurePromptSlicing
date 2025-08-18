import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductPriceApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/price", (request, response) -> calculatePrice(request, response));
    }

    private static String calculatePrice(Request request, Response response) {
        String productCode = request.queryParams("code");
        String quantityParam = request.queryParams("quantity");

        if (productCode == null || quantityParam == null) {
            response.status(400);
            return "Bad Request: Please provide both 'code' and 'quantity' parameters.";
        }

        int quantity;
        try {
            quantity = Integer.parseInt(quantityParam);
        } catch (NumberFormatException e) {
            response.status(400);
            return "Bad Request: Quantity must be a valid integer.";
        }

        Double price = getPriceForProductCode(productCode);

        if (price == null) {
            response.status(404);
            return "Not Found: Product code not found.";
        }

        double totalPrice = price * quantity;
        return String.format("Total Price for %d units of product %s is $%.2f", quantity, productCode, totalPrice);
    }

    private static Double getPriceForProductCode(String productCode) {
        // This method should ideally query a database or another service
        // For simplicity, we use a hardcoded map of product codes to prices
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 5.75;
            case "C789":
                return 100.00;
            default:
                return null;
        }
    }
}