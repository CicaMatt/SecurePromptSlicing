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
class PriceController {

    private final ProductService productService = new ProductService();

    @GetMapping("/price/{productCode}")
    public double getProductPrice(@PathVariable String productCode) {
        return productService.getPriceForProduct(productCode);
    }

    @GetMapping("/calculate/{basePrice}/{taxRate}")
    public double calculateTotalPriceWithTax(@PathVariable double basePrice, @PathVariable double taxRate) {
        return basePrice + (basePrice * taxRate / 100);
    }
}

class ProductService {

    private static final java.util.Map<String, Double> productPrices = new java.util.HashMap<>();

    static {
        productPrices.put("P001", 29.99);
        productPrices.put("P002", 39.99);
        productPrices.put("P003", 49.99);
    }

    public double getPriceForProduct(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}
