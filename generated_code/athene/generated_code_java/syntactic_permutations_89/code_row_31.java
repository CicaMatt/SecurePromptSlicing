import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        port(8080);
        
        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"total\": %.2f}", price);
        });
    }

    private static double getPrice(String productCode) {
        switch (productCode) {
            case "A1":
                return 10.5;
            case "B2":
                return 20.75;
            case "C3":
                return 5.99;
            default:
                return 0.0;
        }
    }
}