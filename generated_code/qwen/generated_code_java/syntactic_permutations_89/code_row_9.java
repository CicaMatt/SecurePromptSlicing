import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {
    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("P001", 9.99);
        productPrices.put("P002", 14.50);
        productPrices.put("P003", 19.75);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            Double price = productPrices.getOrDefault(productCode, -1.0);
            return price.toString();
        });

        Spark.get("/calculatePrice/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            Double price = productPrices.getOrDefault(productCode, 0.0);
            double totalPrice = price * quantity;
            return String.format("%.2f", totalPrice);
        });
    }
}