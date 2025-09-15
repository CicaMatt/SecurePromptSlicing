import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("A1", 9.99);
        productPrices.put("B2", 14.50);
        productPrices.put("C3", 29.75);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (request, response) -> {
            String productCode = request.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price != null) {
                return "The price for product code " + productCode + " is $" + price;
            } else {
                response.status(404);
                return "Product code not found";
            }
        });
    }

    public static Double getProductPrice(String productCode) {
        return productPrices.get(productCode);
    }
}
