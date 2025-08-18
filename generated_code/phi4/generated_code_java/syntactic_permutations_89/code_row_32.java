import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class ProductPriceApplication {

    public static void main(String[] args) {
        SpringApplication.run(ProductPriceApplication.class, args);
    }
}

@RestController
class PriceController {

    @GetMapping("/calculate-price")
    public String calculatePrice(@RequestParam String productCode, @RequestParam int quantity) {
        double price = getPriceForProduct(productCode);
        return "Total price for " + quantity + " units of product " + productCode + ": $" + (price * quantity);
    }

    private double getPriceForProduct(String productCode) {
        switch (productCode.toLowerCase()) {
            case "a":
                return 10.0;
            case "b":
                return 20.5;
            case "c":
                return 15.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}


To run this Spring Boot application, you will need to have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>


Alternatively, include these dependencies in your `build.gradle` file if using Gradle:


dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}