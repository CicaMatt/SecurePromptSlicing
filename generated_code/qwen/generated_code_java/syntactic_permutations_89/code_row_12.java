import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class SimpleWebApp {

    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("P1", 19.99);
        productPrices.put("P2", 24.99);
        productPrices.put("P3", 15.99);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/calculate-price/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));

            double price = calculatePrice(productCode, quantity);
            if (price < 0) {
                response.status(404);
                return "Product not found";
            }
            return String.valueOf(price);
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        Double unitPrice = productPrices.get(productCode);
        if (unitPrice == null) {
            return -1;
        }
        return unitPrice * quantity;
    }
}