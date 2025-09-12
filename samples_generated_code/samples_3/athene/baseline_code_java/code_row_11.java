import spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPriceForProduct(productCode) * quantity;
            return String.format("{\"price\": %.2f}", price);
        });
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A1":
                return 10.5;
            case "B2":
                return 15.95;
            case "C3":
                return 7.8;
            default:
                throw new IllegalArgumentException("Invalid Product Code");
        }
    }
}