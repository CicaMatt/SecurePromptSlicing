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

    @GetMapping("/calculate-price")
    public String calculatePrice(@RequestParam("productCode") String productCode,
                                @RequestParam("quantity") int quantity) {
        double pricePerUnit = getPriceForProductCode(productCode);
        if (pricePerUnit == -1.0) {
            return "Invalid Product Code";
        }
        double totalPrice = pricePerUnit * quantity;
        return String.format("Total Price for %d units of product code %s is: %.2f", 
                             quantity, productCode, totalPrice);
    }

    private double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                return -1.0; // Invalid product code
        }
    }
}
