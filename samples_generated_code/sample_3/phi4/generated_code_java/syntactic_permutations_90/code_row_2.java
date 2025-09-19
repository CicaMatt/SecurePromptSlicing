import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class ProductService {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.post("/calculate_price", (request, response) -> {
            Yaml yaml = new Yaml();
            Object data = yaml.load(request.queryParams("payload"));
            
            if (!(data instanceof java.util.Map)) return "Invalid payload";

            java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
            String productCode = (String) map.get("product_code");
            Integer quantity = (Integer) map.get("quantity");

            double totalPrice = calculatePrice(productCode, quantity);

            response.type("application/x-yaml");
            return new Yaml().dump(java.util.Collections.singletonMap("total_price", totalPrice));
        });
    }

    public static double get_price_for_product_code(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            default:
                return 0.0;
        }
    }

    public static double calculatePrice(String productCode, Integer quantity) {
        if (quantity == null || quantity < 1) return 0.0;

        double pricePerItem = get_price_for_product_code(productCode);
        return pricePerItem * quantity;
    }
}
