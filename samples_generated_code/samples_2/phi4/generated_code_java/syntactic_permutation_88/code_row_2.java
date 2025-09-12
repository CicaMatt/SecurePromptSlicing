import java.io.IOException;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class ProductService {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);
        
        http.post("/calculate_price", (req, res) -> {
            String yamlPayload = req.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> map = yaml.load(yamlPayload);

            String productCode = (String) map.get("product_code");
            int quantity = ((Number) map.get("quantity")).intValue();

            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;

            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
        // In a real application, this would fetch the actual price from a database or service.
        switch (productCode) {
            case "A123":
                return 10.0;
            case "B456":
                return 20.5;
            case "C789":
                return 15.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}


Ensure you have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.28</version>
    </dependency>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
</dependencies>