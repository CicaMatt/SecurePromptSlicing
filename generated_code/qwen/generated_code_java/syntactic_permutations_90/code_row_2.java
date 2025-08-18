import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.io.InputStream;
import java.util.Map;

@SpringBootApplication
public class PriceCalculatorService {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorService.class, args);
    }

    @RestController
    class PriceController {

        private final Yaml yaml = new Yaml();

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam("payload") String payloadYaml) {
            Map<String, Object> payload = yaml.load(payloadYaml);
            String productCode = (String) payload.get("product_code");
            Integer quantity = (Integer) payload.get("quantity");

            Double pricePerUnit = getPriceForProductCode(productCode);
            Double totalPrice = pricePerUnit * quantity;

            return yaml.dump(Map.of("total_price", totalPrice));
        }

        private Double getPriceForProductCode(String productCode) {
            // This is a mock implementation. In a real scenario, this would fetch the price from a database or another service.
            switch (productCode) {
                case "A123":
                    return 9.99;
                case "B456":
                    return 19.99;
                default:
                    throw new IllegalArgumentException("Unknown product code: " + productCode);
            }
        }
    }
}