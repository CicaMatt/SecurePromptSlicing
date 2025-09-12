import spark.Request;
import spark.Spark;
import org.yaml.snakeyaml.Yaml;
import java.util.Map;

public class PriceMicroservice {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/calculate_price", (Request req, spark.Response res) -> {
            String yamlPayload = req.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = (Integer) data.get("quantity");
            double price = get_price_for_product_code(productCode);
            double totalPrice = price * quantity;
            return new Yaml().dump(Map.of("total_price", totalPrice));
        });
    }

    public static double get_price_for_product_code(String productCode) {
        // This is a mock implementation. In a real scenario, this would fetch the price from a database.
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                return 0.0;
        }
    }
}



<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.28</version>
    </dependency>
</dependencies>