import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class ProductPriceApp {

    public static void main(String[] args) {
        SpringApplication.run(ProductPriceApp.class, args);
    }
}

@RestController
class PriceController {

    private final Map<String, Double> productPrices = Map.of(
            "A001", 19.99,
            "B002", 29.99,
            "C003", 39.99
    );

    @GetMapping("/price/{productCode}")
    public String getPrice(@PathVariable String productCode) {
        return productPrices.getOrDefault(productCode, "Product code not found").toString();
    }
}
