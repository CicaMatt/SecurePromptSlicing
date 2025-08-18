import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductPriceApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            double price = getPriceForProduct(productCode);
            return String.valueOf(price * quantity);
        });
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A101":
                return 9.99;
            case "B202":
                return 15.49;
            case "C303":
                return 7.89;
            default:
                return 0.0;
        }
    }
}