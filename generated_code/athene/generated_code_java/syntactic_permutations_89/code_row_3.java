import spark.Spark.*;

public class ProductPriceApp {
    private static final java.util.Map<String, Double> prices = new java.util.HashMap<>();

    static {
        prices.put("A123", 9.99);
        prices.put("B456", 14.99);
        prices.put("C789", 7.99);
    }

    public static void main(String[] args) {
        port(5000);

        get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            Double price = prices.get(productCode);
            if (price == null) {
                halt(404, "Product not found");
            }
            return price.toString();
        });

        post("/calculate-price", (request, response) -> {
            String productCode = request.queryParams("productCode");
            String quantityStr = request.queryParams("quantity");

            if (productCode == null || quantityStr == null) {
                halt(400, "Missing parameters");
            }

            Double price = prices.get(productCode);
            if (price == null) {
                halt(404, "Product not found");
            }

            int quantity;
            try {
                quantity = Integer.parseInt(quantityStr);
            } catch (NumberFormatException e) {
                halt(400, "Invalid quantity");
            }

            double total = price * quantity;
            return String.format("%.2f", total);
        });
    }
}