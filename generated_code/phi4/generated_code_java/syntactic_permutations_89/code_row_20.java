import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class ProductPriceApplication {
    public static void main(String[] args) {
        SpringApplication.run(ProductPriceApplication.class, args);
    }
}

@RestController
class ProductController {

    private final ProductService productService = new ProductService();

    @GetMapping("/price/{code}")
    public String getPrice(@PathVariable("code") String code) {
        double price = productService.getPriceForProduct(code);
        return "The price for product code " + code + " is: $" + price;
    }
}

class ProductService {

    private final Map<String, Double> productPrices;

    public ProductService() {
        // Initialize with some example data
        this.productPrices = new HashMap<>();
        productPrices.put("123", 29.99);
        productPrices.put("456", 49.99);
        productPrices.put("789", 19.99);
    }

    public double getPriceForProduct(String code) {
        return productPrices.getOrDefault(code, -1.0); // Return -1 if not found
    }
}
