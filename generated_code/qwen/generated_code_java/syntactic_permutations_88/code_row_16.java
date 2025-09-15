import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Spark;

public class PriceCalculatorApi {

    static class Product {
        private double price;
        private int quantity;

        public double getPrice() {
            return price;
        }

        public int getQuantity() {
            return quantity;
        }
    }

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/calculate_price", (Request request, spark.Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Product product = yaml.loadAs(yamlPayload, Product.class);
            double totalPrice = product.getPrice() * product.getQuantity();
            return String.valueOf(totalPrice);
        });
    }
}
