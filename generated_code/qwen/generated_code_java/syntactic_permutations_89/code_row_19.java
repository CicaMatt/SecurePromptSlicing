import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class ProductPriceApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            return String.format("The price for %s is $%.2f", productCode, price);
        });

        Spark.get("/calculate/:productCode/:quantity", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price == null) {
                res.status(404);
                return "Product not found";
            }
            int quantity;
            try {
                quantity = Integer.parseInt(req.params(":quantity"));
            } catch (NumberFormatException e) {
                res.status(400);
                return "Invalid quantity provided";
            }
            double totalPrice = price * quantity;
            return String.format("The total price for %d units of %s is $%.2f", quantity, productCode, totalPrice);
        });
    }

    private static Double getProductPrice(String productCode) {
        return productPrices.get(productCode);
    }
}
