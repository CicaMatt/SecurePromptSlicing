import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/calculatePrice/:productCode/:quantity", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.params(":quantity"));
            double price = getPriceForProduct(productCode);
            return String.format("Total Price for %d units of %s: %.2f", quantity, productCode, price * quantity);
        });
    }

    private static double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}