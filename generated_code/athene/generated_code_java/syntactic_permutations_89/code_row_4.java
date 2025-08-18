import spark.Spark.*;

public class ProductPriceApp {

    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double pricePerUnit = getPriceForProduct(productCode);
            return String.format("%.2f", pricePerUnit * quantity);
        });
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A1":
                return 10.99;
            case "B2":
                return 5.49;
            case "C3":
                return 8.75;
            default:
                return 0.0;
        }
    }
}