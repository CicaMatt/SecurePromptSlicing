import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Spark;

public class ProductPriceApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A123", 19.99);
        productPrices.put("B456", 29.99);
        productPrices.put("C789", 39.99);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode/:quantity", (Request request, Response response) -> {
            String productCode = request.params(":productCode");
            int quantity = Integer.parseInt(request.params(":quantity"));
            double price = getProductPrice(productCode);
            return String.valueOf(price * quantity);
        });
    }

    private static double getProductPrice(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}