import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"price\": %.2f}", price);
        });

        staticFileLocation("/");
    }

    private static double getPrice(String productCode) {
        switch (productCode) {
            case "A1":
                return 10.5;
            case "B2":
                return 20.0;
            case "C3":
                return 15.75;
            default:
                return 0.0;
        }
    }
}