import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        port(5000);
        
        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"total\": %.2f}", price);
        });
    }

    private static double getPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}