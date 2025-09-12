import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {
    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static Double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            Double price = getPriceForProduct(productCode);
            if (price == -1.0) {
                response.status(404);
                return "Product not found";
            }
            return String.format("Price for %s is $%.2f", productCode, price);
        });

        Spark.get("/calculate/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity;
            try {
                quantity = Integer.parseInt(request.params(":quantity"));
            } catch (NumberFormatException e) {
                response.status(400);
                return "Invalid quantity";
            }
            Double price = getPriceForProduct(productCode);
            if (price == -1.0) {
                response.status(404);
                return "Product not found";
            }
            double totalPrice = price * quantity;
            return String.format("Total price for %d of %s is $%.2f", quantity, productCode, totalPrice);
        });
    }
}