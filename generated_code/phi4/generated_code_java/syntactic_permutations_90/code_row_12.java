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


To run the code, you need to include dependencies for Javalin and SnakeYAML in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.8.1</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>2.0</version>
    </dependency>
</dependencies>