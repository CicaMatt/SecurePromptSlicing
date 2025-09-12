import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class PriceCalculatorApi {

    public static void main(String[] args) {
        Spark.get("/calculate_price", (Request request, Response response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;

            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
        // This is a placeholder for actual product pricing logic
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
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