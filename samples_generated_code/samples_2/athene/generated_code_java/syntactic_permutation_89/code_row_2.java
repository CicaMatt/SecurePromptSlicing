import spark.Spark.*;

public class ProductPriceApp {
    private static final java.util.Map<String, Double> productPrices = new java.util.HashMap<>();

    public static void main(String[] args) {
        productPrices.put("A123", 9.99);
        productPrices.put("B456", 14.99);
        productPrices.put("C789", 19.99);

        get("/price/:productCode", (req, res) -> {
            String productCode = req.params(":productCode");
            Double price = productPrices.get(productCode);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            return String.format("%.2f", price);
        });
    }
}