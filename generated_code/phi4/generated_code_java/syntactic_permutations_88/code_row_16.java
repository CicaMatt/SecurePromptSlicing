import org.yaml.snakeyaml.Yaml;
import spark.Service;

import java.util.Map;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        Service http = Service.ignite().port(4567);

        http.get("/calculate_price", (request, response) -> {
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                response.status(400);
                return "Invalid payload";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            if (data == null || !data.containsKey("price") || !data.containsKey("quantity")) {
                response.status(400);
                return "Invalid payload: missing 'price' or 'quantity'";
            }

            double price = (double) data.get("price");
            int quantity = (int) data.get("quantity");

            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
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
        <version>1.33</version>
    </dependency>
</dependencies>