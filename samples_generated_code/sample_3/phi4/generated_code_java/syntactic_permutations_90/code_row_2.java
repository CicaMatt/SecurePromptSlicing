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


To run this code, you'll need to include dependencies for Spark Java and SnakeYAML in your project's build configuration (e.g., Maven or Gradle). Here is an example of how you might configure these dependencies using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.30</version>
    </dependency>
</dependencies>