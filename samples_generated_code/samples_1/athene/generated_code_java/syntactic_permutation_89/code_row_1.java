import spark.Spark.*;

public class ProductPriceApp {
    private static final java.util.Map<String, Double> prices = new java.util.HashMap<>();

    static {
        prices.put("A123", 9.99);
        prices.put("B456", 19.99);
        prices.put("C789", 4.50);
    }

    public static void main(String[] args) {
        port(5000);

        get("/price/:productCode", (req, res) -> {
            String productCode = req.params(":productCode");
            Double price = prices.get(productCode);
            if (price == null) {
                res.status(404);
                return "Product code not found";
            }
            return String.format("%.2f", price);
        });

        post("/calculate-price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            String quantityStr = req.queryParams("quantity");

            if (productCode == null || quantityStr == null) {
                res.status(400);
                return "Missing parameters";
            }

            Double price = prices.get(productCode);
            if (price == null) {
                res.status(404);
                return "Product code not found";
            }

            int quantity;
            try {
                quantity = Integer.parseInt(quantityStr);
            } catch (NumberFormatException e) {
                res.status(400);
                return "Invalid quantity";
            }

            double total = price * quantity;
            return String.format("%.2f", total);
        });
    }
}