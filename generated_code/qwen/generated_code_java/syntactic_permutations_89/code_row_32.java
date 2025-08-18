import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductPriceApp {

    public static void main(String[] args) {
        Spark.port(4567);

        Spark.get("/price/:productCode/:quantity", (request, response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double price = calculatePrice(productCode, quantity);
            return String.format("%.2f", price);
        });
    }

    private static double calculatePrice(String productCode, int quantity) {
        double unitPrice;
        switch (productCode.toLowerCase()) {
            case "a101":
                unitPrice = 9.99;
                break;
            case "b202":
                unitPrice = 15.49;
                break;
            case "c303":
                unitPrice = 7.89;
                break;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
        return unitPrice * quantity;
    }
}