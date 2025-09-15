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
