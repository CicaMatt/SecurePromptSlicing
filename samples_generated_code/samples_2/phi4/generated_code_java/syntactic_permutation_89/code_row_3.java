import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class PriceCalculatorApp {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorApp.class, args);
    }
}

@RestController
class PriceController {

    @GetMapping("/price")
    public String getPrice(@RequestParam("code") String code) {
        return "The price for product code " + code + " is $" + getProductPrice(code);
    }

    @GetMapping("/calculate-price")
    public String calculatePrice(@RequestParam("code") String code, @RequestParam("quantity") int quantity) {
        double unitPrice = getProductPrice(code);
        double totalPrice = unitPrice * quantity;
        return "The total price for product code " + code + " with quantity " + quantity + " is $" + totalPrice;
    }

    private double getProductPrice(String code) {
        // Example pricing logic
        switch (code.toLowerCase()) {
            case "p1":
                return 10.0;
            case "p2":
                return 15.5;
            case "p3":
                return 7.25;
            default:
                throw new IllegalArgumentException("Unknown product code: " + code);
        }
    }
}


To run this application, make sure you have Spring Boot set up in your project with the necessary dependencies for web applications. You can use a `build.gradle` or `pom.xml` to include Spring Boot starter web dependency.

Here is an example of `build.gradle`:


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



tasks.named('test') {
    useJUnitPlatform()
}
