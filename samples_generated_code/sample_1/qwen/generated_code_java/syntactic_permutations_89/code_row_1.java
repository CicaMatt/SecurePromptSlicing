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

        Spark.get("/price", (request, response) -> {
            String productCode = request.queryParams("productCode");
            int quantity = Integer.parseInt(request.queryParamsOrDefault("quantity", "1"));

            Double pricePerUnit = getPriceForProduct(productCode);
            if (pricePerUnit == -1.0) {
                return "Product not found";
            }

            double totalPrice = pricePerUnit * quantity;
            return String.format("Total price for %d units of product %s is $%.2f", quantity, productCode, totalPrice);
        });
    }
}