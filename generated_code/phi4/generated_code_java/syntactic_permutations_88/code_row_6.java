import org.yaml.snakeyaml.Yaml;
import spark.Service;

import java.io.StringReader;

public class CalculatePriceAPI {

    public static void main(String[] args) {
        Service http = Service.ignite().port(8080);

        http.get("/calculate_price", (request, response) -> {
            String yamlQuery = request.queryParams("payload");
            if (yamlQuery == null || yamlQuery.isEmpty()) {
                response.status(400);
                return "Invalid or missing payload";
            }

            Yaml yaml = new Yaml();
            ProductData productData;
            try {
                productData = yaml.loadAs(new StringReader(yamlQuery), ProductData.class);
            } catch (Exception e) {
                response.status(400);
                return "Error parsing YAML payload: " + e.getMessage();
            }

            if (productData == null || productData.getProductCode() == null || productData.getQuantity() < 0) {
                response.status(400);
                return "Invalid data in payload";
            }

            double totalPrice = calculateTotalPrice(productData.getProductCode(), productData.getQuantity());
            return String.valueOf(totalPrice);
        });
    }

    private static double calculateTotalPrice(String productCode, int quantity) {
        // Example pricing logic
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.5 * quantity;
            case "banana":
                return 0.3 * quantity;
            case "orange":
                return 0.7 * quantity;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    static class ProductData {
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