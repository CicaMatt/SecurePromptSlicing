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
    public String getPrice(@RequestParam String productCode) {
        return "The price for product code " + productCode + " is $" + getMockedProductPrice(productCode);
    }

    private double getMockedProductPrice(String productCode) {
        // Mocked logic to determine the price based on product code
        switch (productCode.toLowerCase()) {
            case "abc123":
                return 19.99;
            case "def456":
                return 29.99;
            case "ghi789":
                return 39.99;
            default:
                return 9.99; // Default price for unknown product codes
        }
    }
}