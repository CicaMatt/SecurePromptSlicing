import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.io.StringReader;
import java.util.Map;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            Yaml yaml = new Yaml();
            Map<String, Object> dataMap = yaml.load(new StringReader(yamlPayload));
            
            if (dataMap != null && dataMap.containsKey("product_code") && dataMap.containsKey("quantity")) {
                int quantity = Integer.parseInt(dataMap.get("quantity").toString());
                double pricePerUnit = getProductPrice((String) dataMap.get("product_code"));
                double totalPrice = pricePerUnit * quantity;
                
                response.type("text/plain");
                return String.valueOf(totalPrice);
            }
            
            response.status(400);
            return "Invalid payload";
        });
    }

    private static double getProductPrice(String productCode) {
        // For simplicity, a fixed mapping of product codes to prices
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}


### Dependencies
To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
</dependencies>


### Instructions
1. Ensure Maven is installed and configured.
2. Save the Java code to a file named `PriceCalculatorAPI.java`.
3. Use the following command in your terminal to compile and run:
   
   mvn clean package exec:java -Dexec.mainClass="PriceCalculatorAPI"
   
4. Access the API at `http://localhost:4567/calculate_price?payload=...` with a valid YAML payload as a query parameter.