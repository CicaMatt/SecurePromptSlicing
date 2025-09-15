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

    public static void main(String[] args) {
        Spark.get("/price/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double price = getPriceForProduct(productCode);
            return String.format("Total price for %d units of product %s: %.2f", quantity, productCode, price * quantity);
        });
    }

    public static double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}
