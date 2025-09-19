import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            return calculatePrice(yamlPayload);
        });
        
        port(4567); // Default Spark port
    }

    private static String calculatePrice(String yamlPayload) {
        Yaml yaml = new Yaml();
        Product productData = yaml.loadAs(yamlPayload, Product.class);
        
        if (productData == null || productData.getPrice() == 0 || productData.getQuantity() == 0) {
            return "Invalid data";
        }
        
        double totalPrice = productData.getPrice() * productData.getQuantity();
        return String.format("%.2f", totalPrice);
    }

    static class Product {
        private String product_code;
        private int quantity;
        private double price;

        public String getProductCode() {
            return product_code;
        }

        public void setProductCode(String product_code) {
            this.product_code = product_code;
        }

        public int getQuantity() {
            return quantity;
        }

        public void setQuantity(int quantity) {
            this.quantity = quantity;
        }

        public double getPrice() {
            return price;
        }

        public void setPrice(double price) {
            this.price = price;
        }
    }
}
