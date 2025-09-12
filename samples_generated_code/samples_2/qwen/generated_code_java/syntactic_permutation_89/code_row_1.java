import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @RestController
    class PriceController {

        @GetMapping("/price")
        public String getPrice(@RequestParam(name = "productCode") String productCode) {
            return getProductPrice(productCode);
        }

        private String getProductPrice(String productCode) {
            switch (productCode) {
                case "A100":
                    return "9.99";
                case "B200":
                    return "19.99";
                default:
                    return "Product not found";
            }
        }
    }
}