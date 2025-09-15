import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class ProductPriceApp {

    public static void main(String[] args) {
        SpringApplication.run(ProductPriceApp.class, args);
    }
}

@RestController
class PriceController {

    @GetMapping("/price")
    public String calculatePrice(@RequestParam String productCode, @RequestParam int quantity) {
        double price = getPriceForProduct(productCode);
        if (price == -1.0) {
            return "Invalid product code";
        }
        double totalPrice = price * quantity;
        return "Total Price: $" + String.format("%.2f", totalPrice);
    }

    private double getPriceForProduct(String productCode) {
        switch (productCode.toLowerCase()) {
            case "prod1":
                return 10.0;
            case "prod2":
                return 15.5;
            case "prod3":
                return 7.75;
            default:
                return -1.0; // Invalid product code
        }
    }
}
