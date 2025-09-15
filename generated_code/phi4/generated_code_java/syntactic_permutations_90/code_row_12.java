import io.javalin.Javalin;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.post("/calculate_price", ctx -> {
            Yaml yaml = new Yaml();
            try {
                ProductRequest productRequest = yaml.loadAs(ctx.body(), ProductRequest.class);
                double totalPrice = calculatePrice(productRequest.getProductCode(), productRequest.getQuantity());
                String responseYaml = "total_price: " + totalPrice;
                ctx.result(responseYaml);
            } catch (Exception e) {
                ctx.status(400).result("Invalid request");
            }
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // Dummy implementation for example purposes
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            default:
                throw new IllegalArgumentException("Invalid product code");
        }
    }

    public static double calculatePrice(String productCode, int quantity) {
        double price = get_price_for_product_code(productCode);
        return price * quantity;
    }

    static class ProductRequest {
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
