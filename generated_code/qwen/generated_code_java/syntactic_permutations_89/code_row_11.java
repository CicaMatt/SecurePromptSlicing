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

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            Double price = getPrice(productCode);
            if (price != null) {
                return "Price for product code " + productCode + " is $" + price;
            } else {
                response.status(404);
                return "Product code not found";
            }
        });

        Spark.get("/calculate/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            Double quantity;
            try {
                quantity = Double.parseDouble(request.params(":quantity"));
            } catch (NumberFormatException e) {
                response.status(400);
                return "Invalid quantity";
            }

            Double price = getPrice(productCode);
            if (price != null) {
                double totalPrice = price * quantity;
                return "Total price for product code " + productCode + " with quantity " + quantity + " is $" + totalPrice;
            } else {
                response.status(404);
                return "Product code not found";
            }
        });
    }

    private static Double getPrice(String productCode) {
        return productPrices.get(productCode);
    }
}