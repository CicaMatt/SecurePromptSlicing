import org.yaml.snakeyaml.Yaml;
import spark.Spark;

public class SimpleAPI {

    public static void main(String[] args) {
        Spark.port(4567);
        
        Spark.post("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;

            response.type("text/plain");
            return String.valueOf(totalPrice);
        });
    }

    private static double getProductPrice(String productCode) {
        // Dummy implementation for example purposes
        switch (productCode) {
            case "A1":
                return 10.0;
            case "B2":
                return 20.0;
            case "C3":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}


To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.29</version>
    </dependency>
</dependencies>