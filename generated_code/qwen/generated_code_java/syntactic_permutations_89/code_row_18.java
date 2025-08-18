import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebAppApplication.class, args);
    }

    @RestController
    class PriceController {

        @GetMapping("/price")
        public String getPrice(@RequestParam(name = "productCode") String productCode) {
            return "The price for product code " + productCode + " is $" + getProductPrice(productCode);
        }

        private double getProductPrice(String productCode) {
            // Dummy implementation, replace with actual logic
            switch (productCode) {
                case "A123":
                    return 19.99;
                case "B456":
                    return 29.99;
                default:
                    return 0.0;
            }
        }
    }
}