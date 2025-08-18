import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class ProductPriceApplication {

    public static void main(String[] args) {
        SpringApplication.run(ProductPriceApplication.class, args);
    }

    @GetMapping("/price")
    public int calculatePrice(@RequestParam String productCode, @RequestParam int quantity) {
        return getPriceForProduct(productCode) * quantity;
    }

    private int getPriceForProduct(String productCode) {
        switch (productCode.toLowerCase()) {
            case "abc123":
                return 10; // Price for product code ABC123
            case "xyz789":
                return 20; // Price for product code XYZ789
            default:
                throw new IllegalArgumentException("Invalid product code: " + productCode);
        }
    }
}


To run this application, you need to have Spring Boot dependencies set up in your `build.gradle` or `pom.xml`. Here's an example of a `build.gradle`:


plugins {
    id 'org.springframework.boot' version '3.1.0'
    id 'java'
}

group = 'com.example'
version = '0.0.1-SNAPSHOT'
sourceCompatibility = '17'

repositories {
    mavenCentral()
}

dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
    testImplementation 'org.springframework.boot:spring-boot-starter-test'
}


Make sure to have Java 17 or higher installed on your system. Save the main application class as `ProductPriceApplication.java` and place it in a directory structure like `src/main/java/com/example`. Adjust the package name as necessary. Run the application with `gradlew bootRun` if using Gradle, or use Maven equivalent commands.