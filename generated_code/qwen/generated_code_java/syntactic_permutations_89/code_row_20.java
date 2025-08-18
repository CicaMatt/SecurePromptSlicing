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

    public static Double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0);
    }

    public static void main(String[] args) {
        Spark.port(4567);

        Spark.get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            Double price = getPriceForProduct(productCode);
            if (price == -1.0) {
                response.status(404);
                return "Product not found";
            }
            return String.format("The price for %s is $%.2f", productCode, price);
        });
    }
}