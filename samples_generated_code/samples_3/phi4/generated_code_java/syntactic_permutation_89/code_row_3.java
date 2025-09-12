import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class PriceApplication {

    public static void main(String[] args) {
        SpringApplication.run(PriceApplication.class, args);
    }
}

@RestController
class PriceController {

    @GetMapping("/price")
    public double calculatePrice(@RequestParam String productCode, @RequestParam int quantity) {
        double pricePerUnit = getPriceForProduct(productCode);
        return pricePerUnit * quantity;
    }

    private double getPriceForProduct(String productCode) {
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.75;
            case "banana":
                return 0.50;
            case "orange":
                return 1.00;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}


To run the above Spring Boot application, ensure you have the necessary dependencies in your `pom.xml`:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
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


You can package and run the application using Maven:


mvn spring-boot:run


The application will be accessible at `http://localhost:5000/price`.