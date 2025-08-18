import spark.Spark.*;
import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {
    private static Map<String, Double> productPrices = new HashMap<>();

    public static void main(String[] args) {
        productPrices.put("A123", 9.99);
        productPrices.put("B456", 14.99);
        productPrices.put("C789", 19.99);

        get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price == null) {
                response.status(404);
                return "Product not found";
            } else {
                return String.format("{\"price\": %.2f}", price);
            }
        });
    }

    private static Double getProductPrice(String productCode) {
        return productPrices.get(productCode);
    }
}