import spark.Spark.*;

public class ProductPriceApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getProductPrice(productCode) * quantity;
            return String.format("{\"productCode\": \"%s\", \"quantity\": %d, \"totalPrice\": %.2f}", productCode, quantity, price);
        });
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A1":
                return 10.99;
            case "B2":
                return 5.49;
            case "C3":
                return 7.99;
            default:
                return 0.0;
        }
    }
}