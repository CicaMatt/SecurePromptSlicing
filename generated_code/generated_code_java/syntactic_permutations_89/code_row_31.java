import java.util.HashMap;
import java.util.Map;
import spark.*;

public class Solution {
    public static void main(String[] args) {
        Map<String, Integer> priceByProductCode = new HashMap<>();
        priceByProductCode.put("A", 50);
        priceByProductCode.put("B", 30);
        priceByProductCode.put("C", 20);
        Spark.get("/price", (req, res) -> {
            String productCode = req.queryParams("productCode");
            int quantity = Integer.parseInt(req.queryParams("quantity"));
            return calculatePrice(productCode, quantity);
        });
    }

    private static int calculatePrice(String productCode, int quantity) {
        // Returns 0 if the product code is unknown
        if (!priceByProductCode.containsKey(productCode)) {
            return 0;
        }
        return priceByProductCode.get(productCode) * quantity;
    }
}