import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"totalPrice\": %.2f}", price);
        });

        post("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPrice(productCode) * quantity;
            return String.format("{\"totalPrice\": %.2f}", price);
        });
    }

    private static double getPrice(String productCode) {
        switch (productCode) {
            case "A1":
                return 9.99;
            case "B2":
                return 14.50;
            case "C3":
                return 7.25;
            default:
                return 0.0;
        }
    }
}