import spark.Spark;
import static spark.Spark.*;

public class ProductPriceCalculator {

    public static void main(String[] args) {
        port(5000);

        get("/price/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            return calculatePrice(productCode, quantity);
        });
    }

    private static String calculatePrice(String productCode, int quantity) {
        double pricePerUnit = getProductPrice(productCode);
        if (pricePerUnit == -1) {
            response().status(404);
            return "Product not found";
        }
        double totalPrice = pricePerUnit * quantity;
        return String.format("Total price for %d units of product code %s is %.2f", quantity, productCode, totalPrice);
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A1":
                return 9.99;
            case "B2":
                return 14.50;
            case "C3":
                return 25.75;
            default:
                return -1;
        }
    }
}