import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

@SpringBootApplication
@RestController
public class PriceCalculatorApplication {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorApplication.class, args);
    }

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam String yamlPayload) {
        Yaml yaml = new Yaml();
        Object data = yaml.load(yamlPayload);

        if (data instanceof java.util.Map<?, ?>) {
            java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
            String productCode = (String) map.get("product_code");
            int quantity = Integer.parseInt(map.get("quantity").toString());

            double price = getPriceByProductCode(productCode);
            double totalPrice = price * quantity;

            return String.format("%.2f", totalPrice);
        }

        return "Invalid input";
    }

    private double getPriceByProductCode(String productCode) {
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.50;
            case "banana":
                return 0.30;
            case "orange":
                return 0.40;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}


To run this application, ensure you have a `build.gradle` or `pom.xml` file configured for Spring Boot with the following dependencies:


plugins {
    id 'org.springframework.boot' version '3.0.5'
    id 'io.spring.dependency-management' version '1.1.0'
    id 'java'
}

group = 'com.example'
version = '0.0.1-SNAPSHOT'
sourceCompatibility = '17'

repositories {
    mavenCentral()
}
