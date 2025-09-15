import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            ProductDetails productDetails = yaml.loadAs(yamlPayload, ProductDetails.class);
            double totalPrice = calculateTotalPrice(productDetails.product_code, productDetails.quantity);
            return String.valueOf(totalPrice);
        });
    }

    private static double calculateTotalPrice(String productCode, int quantity) {
        double price = getProductPrice(productCode);
        return price * quantity;
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A001":
                return 9.99;
            case "B002":
                return 4.50;
            default:
                return 0.0;
        }
    }

    private static class ProductDetails {
        public String product_code;
        public int quantity;
    }
}
