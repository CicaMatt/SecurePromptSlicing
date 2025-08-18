import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class ProductPriceApp {
    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.95);
        productPrices.put("C789", 9.99);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (req, res) -> {
            String productCode = req.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            return String.format("%.2f", price);
        });

        Spark.get("/total/:productCode/:quantity", (req, res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.params(":quantity"));
            Double price = getProductPrice(productCode);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            double total = price * quantity;
            return String.format("%.2f", total);
        });
    }

    private static Double getProductPrice(String productCode) {
        return productPrices.get(productCode);
    }
}