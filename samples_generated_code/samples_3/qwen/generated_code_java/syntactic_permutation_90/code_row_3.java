import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class MicroserviceApplication {

    public static void main(String[] args) {
        SpringApplication.run(MicroserviceApplication.class, args);
    }

    @RestController
    class PriceController {

        private final Map<String, Double> productPrices = new HashMap<>() {{
            put("A123", 19.99);
            put("B456", 29.99);
            put("C789", 39.99);
        }};

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String yamlPayload) {
            Yaml yaml = new Yaml();
            Map<String, Integer> items = yaml.load(yamlPayload);

            double totalPrice = 0.0;
            for (Map.Entry<String, Integer> entry : items.entrySet()) {
                String productCode = entry.getKey();
                int quantity = entry.getValue();
                Double price = get_price_for_product_code(productCode);
                if (price != null) {
                    totalPrice += price * quantity;
                }
            }

            Map<String, Double> response = new HashMap<>();
            response.put("totalPrice", totalPrice);
            return yaml.dump(response);
        }

        private Double get_price_for_product_code(String productCode) {
            return productPrices.get(productCode);
        }
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.7.5</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>
    <groupId>com.example</groupId>
    <artifactId>microservice</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>microservice</name>
    <description>Demo project for Spring Boot</description>
    <properties>
        <java.version>11</java.version>
    </properties>
    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        <dependency>
            <groupId>org.yaml</groupId>
            <artifactId>snakeyaml</artifactId>
            <version>1.29</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
</project>