import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A1", 19.99);
        productPrices.put("B2", 5.49);
        productPrices.put("C3", 23.75);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode/:quantity", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.params(":quantity"));
            double price = getPriceForProduct(productCode);
            if (price == -1) {
                res.status(404);
                return "Product not found";
            }
            double totalPrice = price * quantity;
            return String.format("Total price for %d of product %s is: %.2f", quantity, productCode, totalPrice);
        });
    }

    private static double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode.toUpperCase(), -1.0);
    }
}