import org.yaml.snakeyaml.*;
import spark.*;
public class Main {
    public static void main(String[] args) {
        Spark.get("/calculate_price", (req, res) -> {
            String yaml = req.queryParams("payload");
            Yaml y = new Yaml();
            Map<String, Object> data = (Map<String, Object>) y.load(yaml);
            int quantity = Integer.parseInt((String) data.get("quantity"));
            double price = get_price_for_product_code((String) data.get("product_code"));
            return String.format("total_price: %f", price * quantity);
        });
    }
    static double get_price_for_product_code(String code) {
        if ("VOUCHER".equals(code)) {
            return 5.0;
        } else if ("TSHIRT".equals(code)) {
            return 20.0;
        } else if ("MUG".equals(code)) {
            return 7.5;
        }
        throw new IllegalArgumentException("Product code does not exist");
    }
}