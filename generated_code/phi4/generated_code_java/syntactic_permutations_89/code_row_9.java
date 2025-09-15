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
