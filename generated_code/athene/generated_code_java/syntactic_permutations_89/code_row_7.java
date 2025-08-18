import spark.Spark.*;

public class ProductPriceApp {
    private static final java.util.Map<String, Double> prices = new java.util.HashMap<>();
    
    static {
        prices.put("A123", 9.99);
        prices.put("B456", 14.50);
        prices.put("C789", 19.95);
    }

    public static void main(String[] args) {
        port(5000);

        get("/price/:productCode", (req, res) -> {
            String productCode = req.params(":productCode");
            Double price = prices.get(productCode);
            if (price == null) {
                halt(404, "Product code not found");
            }
            return price.toString();
        });

        post("/calculate-price", (req, res) -> {
            String body = req.body();
            String[] params = body.split(",");
            if (params.length != 2) {
                halt(400, "Invalid request format. Use: productCode,quantity");
            }
            String productCode = params[0].trim();
            int quantity;
            try {
                quantity = Integer.parseInt(params[1].trim());
            } catch (NumberFormatException e) {
                halt(400, "Quantity must be a valid integer");
            }

            Double price = prices.get(productCode);
            if (price == null) {
                halt(404, "Product code not found");
            }
            double total = price * quantity;
            return String.format("%.2f", total);
        });
    }
}