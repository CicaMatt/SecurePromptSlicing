import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = calculatePrice(productCode, quantity);
            return String.format("{\"price\": %.2f}", price);
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        switch (productCode) {
            case "A":
                return 10.0 * quantity;
            case "B":
                return 20.0 * quantity;
            default:
                return 0.0;
        }
    }
}