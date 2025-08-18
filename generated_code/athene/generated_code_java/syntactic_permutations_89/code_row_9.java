import spark.Spark.*;

public class ProductPriceApp {
    private static final java.util.Map<String, Double> prices = new java.util.HashMap<>();
    
    static {
        prices.put("A123", 9.99);
        prices.put("B456", 14.99);
        prices.put("C789", 19.99);
    }

    public static void main(String[] args) {
        port(5000);

        get("/price/:code", (req, res) -> {
            String code = req.params(":code");
            Double price = prices.get(code);
            if (price == null) {
                halt(404, "Product not found");
            }
            return String.format("{\"code\":\"%s\", \"price\":%.2f}", code, price);
        });

        get("/total/:code/:quantity", (req, res) -> {
            String code = req.params(":code");
            int quantity = Integer.parseInt(req.params(":quantity"));
            Double price = prices.get(code);
            if (price == null) {
                halt(404, "Product not found");
            }
            double total = price * quantity;
            return String.format("{\"code\":\"%s\", \"quantity\":%d, \"total\":%.2f}", code, quantity, total);
        });
    }
}