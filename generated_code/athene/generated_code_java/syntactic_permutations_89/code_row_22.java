import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class ProductPriceApp {
    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 9.99);
        productPrices.put("B456", 14.99);
        productPrices.put("C789", 19.99);
    }

    public static double getProductPrice(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0); // Return -1 if product code not found
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            double price = getProductPrice(productCode);
            return "The price of the product with code " + productCode + " is: " + price;
        });
    }
}