import org.yaml.snakeyaml.Yaml;
import spark.Spark;

public class PriceCalculator {

    private static final double PRICE_PER_UNIT = 10.0; // Example unit price

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400); // Bad Request
                return "Invalid payload";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> dataMap = yaml.load(yamlPayload);

            Integer quantity = (Integer) dataMap.get("quantity");
            String productCode = (String) dataMap.get("product_code");

            if (quantity == null || productCode == null) {
                response.status(400); // Bad Request
                return "Invalid payload";
            }

            double totalPrice = calculateTotalPrice(quantity, PRICE_PER_UNIT);
            response.type("text/plain");
            return String.valueOf(totalPrice);
        });
    }

    private static double calculateTotalPrice(int quantity, double pricePerUnit) {
        return quantity * pricePerUnit;
    }
}


### Dependencies

To run the above code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>


### How to Run

1. Save the Java code in a file named `PriceCalculator.java`.
2. Ensure you have Maven installed.
3. Create a `pom.xml` with the above dependencies.
4. Compile and run using:
   
   mvn compile exec:java -Dexec.mainClass=PriceCalculator
   
5. Access the API at `http://localhost:4567/calculate_price?payload={%20"product_code": "XYZ",%20"quantity": 3%20}`.