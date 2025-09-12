import spark.Spark.*;

public class ProductPriceApp {
    private static final java.util.Map<String, Double> prices = new java.util.HashMap<>();
    
    static {
        prices.put("A123", 19.99);
        prices.put("B456", 29.99);
        prices.put("C789", 15.00);
    }

    public static void main(String[] args) {
        port(5000);

        get("/price/:productCode", (req, res) -> {
            String productCode = req.params(":productCode");
            Double price = prices.get(productCode);
            if (price == null) {
                halt(404, "Product code not found");
            }
            return "{\"productCode\": \"" + productCode + "\", \"price\": " + price + "}";
        });

        get("/total/:productCode/:quantity", (req, res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.params(":quantity"));
            Double price = prices.get(productCode);
            if (price == null) {
                halt(404, "Product code not found");
            }
            double total = price * quantity;
            return "{\"productCode\": \"" + productCode + "\", \"quantity\": " + quantity + ", \"total\": " + total + "}";
        });
    }
}