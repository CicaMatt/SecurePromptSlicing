import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductPriceApp {

    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 5.75);
        productPrices.put("C789", 32.50);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/calculatePrice", (Request request, Response response) -> {
            String productCode = request.queryParams("productCode");
            int quantity = Integer.parseInt(request.queryParams("quantity"));

            double price = calculateTotalPrice(productCode, quantity);
            return "Total Price: $" + price;
        });
    }

    private static double calculateTotalPrice(String productCode, int quantity) {
        Double unitPrice = productPrices.getOrDefault(productCode, 0.0);
        return unitPrice * quantity;
    }
}