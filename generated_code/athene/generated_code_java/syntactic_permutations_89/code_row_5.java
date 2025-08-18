import spark.Spark.*;

public class ProductPriceApp {

    public static void main(String[] args) {
        port(5000);

        get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getProductPrice(productCode) * quantity;
            return "Total Price: $" + price;
        });
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 9.99;
            case "B456":
                return 14.99;
            case "C789":
                return 19.99;
            default:
                return 0.0;
        }
    }
}