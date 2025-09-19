import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static Double getPrice(String productCode) {
        return productPrices.getOrDefault(productCode, null);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode/:quantity", (Request request, Response response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            Double pricePerUnit = getPrice(productCode);
            if (pricePerUnit == null) {
                response.status(404);
                return "Product not found";
            }
            double totalPrice = pricePerUnit * quantity;
            return String.format("Total price for %d units of product %s: $%.2f", quantity, productCode, totalPrice);
        });
    }
}