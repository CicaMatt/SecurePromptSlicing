import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            ProductOrder productOrder = yaml.loadAs(yamlPayload, ProductOrder.class);
            
            double totalPrice = calculateTotalPrice(productOrder.getProductCode(), productOrder.getQuantity());
            return String.valueOf(totalPrice);
        });
    }

    private static double calculateTotalPrice(String productCode, int quantity) {
        double price;
        switch (productCode) {
            case "A123":
                price = 19.99;
                break;
            case "B456":
                price = 29.99;
                break;
            default:
                price = 0.0;
        }
        return price * quantity;
    }

    static class ProductOrder {
        private String productCode;
        private int quantity;

        public String getProductCode() {
            return productCode;
        }

        public void setProductCode(String productCode) {
            this.productCode = productCode;
        }

        public int getQuantity() {
            return quantity;
        }

        public void setQuantity(int quantity) {
            this.quantity = quantity;
        }
    }
}