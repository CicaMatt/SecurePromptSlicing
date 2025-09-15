import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApp {
    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }
}

@RestController
class ProductController {

    @GetMapping("/product/{code}")
    public String getProductCode(@PathVariable String code) {
        return "Product Code: " + code;
    }

    @GetMapping("/calculate")
    public String calculatePrice(@RequestParam String code, @RequestParam int quantity) {
        double pricePerUnit = getPriceForCode(code);
        double totalPrice = pricePerUnit * quantity;
        return "Total Price for Product Code " + code + ": $" + totalPrice;
    }

    private double getPriceForCode(String code) {
        switch (code.toLowerCase()) {
            case "a":
                return 10.0;
            case "b":
                return 20.5;
            case "c":
                return 15.75;
            default:
                return 0.0; // Default price if the product code is not recognized
        }
    }
}
