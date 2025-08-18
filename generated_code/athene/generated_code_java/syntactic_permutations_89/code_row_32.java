import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class ProductPriceApp {
    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 9.99);
        productPrices.put("B456", 14.50);
        productPrices.put("C789", 19.99);
    }

    public static void main(String[] args) {
        Spark.get("/price/:productCode/:quantity", (req, res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.params(":quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"total\": %.2f}", price);
        });
    }

    private static double getPrice(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}