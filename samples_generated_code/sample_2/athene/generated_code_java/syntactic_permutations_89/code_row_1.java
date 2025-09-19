import spark.Spark.*;

public class ProductPriceApp {
    private static final java.util.Map<String, Double> productPrices = new java.util.HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static double getPrice(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0);
    }

    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(productCode);
            if (price == -1.0) {
                res.status(404);
                return "Product not found";
            }
            double total = price * quantity;
            return String.format("{ \"total\": %.2f }", total);
        });
    }
}