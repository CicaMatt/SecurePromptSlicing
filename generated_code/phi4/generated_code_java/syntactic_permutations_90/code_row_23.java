import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import spark.Service;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class MicroserviceExample {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.get("/calculate_price", (req, res) -> {
            String yamlPayload = req.queryParams("yaml");
            Map<String, Object> map;
            try {
                ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
                map = mapper.readValue(yamlPayload, HashMap.class);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            double totalPrice = calculateTotalPrice(map);

            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);

            try {
                ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
                return mapper.writeValueAsString(result);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });

        System.out.println("Microservice running on port 4567");
    }

    private static double calculateTotalPrice(Map<String, Object> map) {
        Map<String, Integer> products = (Map<String, Integer>) map.get("products");

        if (products == null) return 0.0;

        double totalPrice = 0.0;
        for (Map.Entry<String, Integer> entry : products.entrySet()) {
            String productCode = entry.getKey();
            int quantity = entry.getValue();
            double price = getPriceForProductCode(productCode);
            totalPrice += price * quantity;
        }

        return totalPrice;
    }

    private static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}


Make sure to include the following dependencies in your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.14.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>