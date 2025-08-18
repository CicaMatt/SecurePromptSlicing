import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String product = req.queryParams("product");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(product) * quantity;
            return String.format("{\"product\": \"%s\", \"quantity\": %d, \"totalPrice\": %.2f}", product, quantity, price);
        });

        staticFileLocation("/public");
    }

    private static double getPrice(String product) {
        switch (product.toLowerCase()) {
            case "apple":
                return 0.5;
            case "banana":
                return 0.3;
            case "orange":
                return 0.4;
            default:
                return 0.0;
        }
    }
}