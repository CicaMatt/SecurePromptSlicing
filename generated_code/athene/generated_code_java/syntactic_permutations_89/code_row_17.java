import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class ProductPriceApp {
    private static final Map<String, Double> prices = new HashMap<>();

    static {
        prices.put("A123", 9.99);
        prices.put("B456", 14.50);
        prices.put("C789", 19.99);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:code", (req, res) -> {
            String code = req.params(":code");
            Double price = prices.get(code);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            return String.format("%.2f", price);
        });

        Spark.get("/total/:code/:quantity", (req, res) -> {
            String code = req.params(":code");
            int quantity = Integer.parseInt(req.params(":quantity"));
            Double price = prices.get(code);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            double total = price * quantity;
            return String.format("%.2f", total);
        });
    }
}