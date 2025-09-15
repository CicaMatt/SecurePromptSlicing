import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {

    private static Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static Double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            Double price = getPriceForProduct(productCode);
            if (price == -1.0) {
                res.status(404);
                return "Product not found";
            }
            return String.format("Price for %s: $%.2f", productCode, price);
        });

        Spark.get("/calculate/:productCode/:quantity", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            int quantity;
            try {
                quantity = Integer.parseInt(req.params(":quantity"));
            } catch (NumberFormatException e) {
                res.status(400);
                return "Invalid quantity";
            }
            Double price = getPriceForProduct(productCode);
            if (price == -1.0) {
                res.status(404);
                return "Product not found";
            }
            double totalPrice = price * quantity;
            return String.format("Total price for %d of %s: $%.2f", quantity, productCode, totalPrice);
        });
    }
}
