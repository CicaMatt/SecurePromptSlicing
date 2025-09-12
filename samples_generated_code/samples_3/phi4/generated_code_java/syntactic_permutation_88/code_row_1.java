import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

import java.util.Map;

public class PriceCalculatorAPI {
    public static void main(String[] args) {
        post("/calculate_price", (request, response) -> {
            response.type("text/plain");
            String yamlPayload = request.queryParams("payload");
            if (yamlPayload == null || yamlPayload.isEmpty()) {
                return "Error: Missing payload";
            }
            
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            Integer price = (Integer) data.get("price");
            Integer quantity = (Integer) data.get("quantity");

            if (price == null || quantity == null) {
                return "Error: Invalid payload";
            }

            int totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        });
    }
}


To run this code, you need to include the following dependencies in your project:

1. Spark Java for creating the web API.
2. SnakeYAML for parsing YAML payloads.

You can add these dependencies to your `pom.xml` if using Maven:


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


Or to your `build.gradle` if using Gradle:


dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
    implementation 'org.yaml:snakeyaml:1.33'
}