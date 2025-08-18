import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("P001", 19.99);
        productPrices.put("P002", 5.49);
        productPrices.put("P003", 3.75);
    }

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/price/:productCode", (Request req, Response res) -> {
            String productCode = req.params(":productCode");
            Double price = getProductPrice(productCode);
            if (price != null) {
                res.type("application/json");
                return "{\"productCode\":\"" + productCode + "\", \"price\":" + price + "}";
            } else {
                res.status(404);
                return "{\"error\":\"Product not found\"}";
            }
        });
    }

    public static Double getProductPrice(String productCode) {
        return productPrices.get(productCode);
    }
}