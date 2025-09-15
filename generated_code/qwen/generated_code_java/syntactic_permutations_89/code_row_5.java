import spark.Spark;
import static spark.Spark.get;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);

        get("/price/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double pricePerUnit = getPriceForProduct(productCode);
            double totalPrice = pricePerUnit * quantity;
            return "Total Price for " + quantity + " units of product " + productCode + ": $" + totalPrice;
        });
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            case "C789":
                return 39.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}
