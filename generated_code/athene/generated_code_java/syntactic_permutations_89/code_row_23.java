import spark.Spark.*;
import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {
    private static final Map<String, Double> productPrices = new HashMap<>();

    public static void main(String[] args) {
        port(5000);

        // Initialize some product prices
        productPrices.put("A123", 9.99);
        productPrices.put("B456", 19.95);
        productPrices.put("C789", 5.49);

        get("/price/:productCode", (req, res) -> {
            String productCode = req.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            return String.format("{\"productCode\": \"%s\", \"price\": %.2f}", productCode, price);
        });
    }

    private static Double getProductPrice(String productCode) {
        return productPrices.get(productCode);
    }
}