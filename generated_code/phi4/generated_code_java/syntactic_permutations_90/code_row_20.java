import io.javalin.Javalin;
import io.javalin.http.Context;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/calculate_price", ctx -> {
            String yamlQuery = ctx.queryParam("payload");
            if (yamlQuery != null && !yamlQuery.isEmpty()) {
                Yaml yaml = new Yaml();
                ProductRequest productRequest = yaml.loadAs(yamlQuery, ProductRequest.class);

                double totalPrice = calculateTotalPrice(productRequest.getProductCode(), productRequest.getQuantity());
                
                String resultYaml = yaml.dump(Map.of("total_price", totalPrice));
                ctx.result(resultYaml);
            } else {
                ctx.status(400).result("Invalid payload");
            }
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // Example product prices
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.50;
            case "banana":
                return 0.30;
            case "cherry":
                return 1.00;
            default:
                return -1; // Invalid product code
        }
    }

    public static double calculateTotalPrice(String productCode, int quantity) {
        double price = get_price_for_product_code(productCode);
        
        if (price == -1) {
            throw new IllegalArgumentException("Invalid product code");
        }
        
        return price * quantity;
    }

    private static class ProductRequest {
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