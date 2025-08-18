import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"price\": %.2f}", price);
        });
    }

    private static double getPrice(String productCode) {
        switch (productCode) {
            case "A":
                return 10.50;
            case "B":
                return 15.75;
            case "C":
                return 7.99;
            default:
                return 0.00;
        }
    }
}