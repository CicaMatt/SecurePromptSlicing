import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class PriceCalculatorApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 9.99);
        productPrices.put("B456", 14.50);
        productPrices.put("C789", 29.99);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode/:quantity", (Request request, Response response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            Double price = getPriceForProduct(productCode);
            if (price == null) {
                response.status(404);
                return "Product code not found";
            }
            double totalPrice = price * quantity;
            return String.format("Total price for %d units of product %s is %.2f", quantity, productCode, totalPrice);
        });
    }

    public static Double getPriceForProduct(String productCode) {
        return productPrices.get(productCode);
    }
}