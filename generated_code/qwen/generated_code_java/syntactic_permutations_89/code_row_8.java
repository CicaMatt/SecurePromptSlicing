import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/price", SimpleWebApp::calculatePrice);
    }

    private static String calculatePrice(Request request, Response response) {
        String productCode = request.queryParams("productCode");
        int quantity = Integer.parseInt(request.queryParams("quantity"));
        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;
        return "Total Price: $" + totalPrice;
    }

    private static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A1":
                return 9.99;
            case "B2":
                return 4.50;
            case "C3":
                return 19.99;
            default:
                return 0.0;
        }
    }
}
