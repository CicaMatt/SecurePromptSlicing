import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPriceForProduct(productCode);
            return String.format("{\"total\": %.2f}", price * quantity);
        });

        post("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPriceForProduct(productCode);
            return String.format("{\"total\": %.2f}", price * quantity);
        });
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A1":
                return 10.50;
            case "B2":
                return 20.75;
            case "C3":
                return 5.99;
            default:
                return 0.0;
        }
    }
}