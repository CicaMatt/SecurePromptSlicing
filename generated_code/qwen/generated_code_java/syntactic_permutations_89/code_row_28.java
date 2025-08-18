import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/price/:productCode/:quantity", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            int quantity = Integer.parseInt(req.params(":quantity"));
            double price = calculatePrice(productCode, quantity);
            return "The total price for " + quantity + " of product code " + productCode + " is: $" + price;
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        // Example pricing logic
        double unitPrice;
        switch (productCode) {
            case "A101":
                unitPrice = 9.99;
                break;
            case "B202":
                unitPrice = 15.49;
                break;
            case "C303":
                unitPrice = 7.89;
                break;
            default:
                unitPrice = 0.0;
        }
        return unitPrice * quantity;
    }
}