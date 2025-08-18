import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class ProductPriceApp {

    public static void main(String[] args) {
        SpringApplication.run(ProductPriceApp.class, args);
    }

    @Bean
    public ProductService productService() {
        return new SimpleProductService();
    }
}

@RestController
class PriceController {

    private final ProductService productService;

    public PriceController(ProductService productService) {
        this.productService = productService;
    }

    @GetMapping("/product-price")
    public double getProductPrice(@RequestParam String productCode, @RequestParam int quantity) {
        double pricePerUnit = productService.getPriceForProduct(productCode);
        return pricePerUnit * quantity;
    }
}

interface ProductService {
    double getPriceForProduct(String productCode);
}

class SimpleProductService implements ProductService {

    private final java.util.Map<String, Double> productPrices;

    public SimpleProductService() {
        this.productPrices = new java.util.HashMap<>();
        // Example product prices
        productPrices.put("A", 10.0);
        productPrices.put("B", 15.5);
        productPrices.put("C", 7.25);
    }

    @Override
    public double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}


To run this Java Spring Boot application:

1. Ensure you have JDK and Maven installed.
2. Create a new directory for your project.
3. Place the above code in `src/main/java/com/example/productpriceapp/ProductPriceApp.java` (adjust package name as needed).
4. Create a `pom.xml` file with the necessary dependencies for Spring Boot.


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>productpriceapp</artifactId>
    <version>1.0-SNAPSHOT</version>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.5.4</version>
        <relativePath/>
    </parent>

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
</project>


5. Run `mvn spring-boot:run` in the terminal within your project directory to start the application.