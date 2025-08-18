import spark.Spark;

import static spark.Spark.get;
import static spark.Spark.port;

public class SimpleWebApp {
    public static void main(String[] args) {
        port(5000);

        get("/price/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double price = calculatePrice(productCode, quantity);
            return String.format("The price for %d units of product %s is %.2f", quantity, productCode, price);
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        // Dummy implementation
        double basePrice;
        switch (productCode) {
            case "A1":
                basePrice = 10.0;
                break;
            case "B2":
                basePrice = 20.0;
                break;
            default:
                basePrice = 5.0;
        }
        return basePrice * quantity;
    }
}