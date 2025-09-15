import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

@SpringBootApplication
public class PriceCalculatorApplication {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorApplication.class, args);
    }

    @RestController
    class PriceController {

        private final Map<String, Double> productPrices = Map.of(
                "A123", 9.99,
                "B456", 19.99,
                "C789", 29.99
        );

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String payload) {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Integer) data.get("quantity")).intValue();

            double price = productPrices.getOrDefault(productCode, 0.0) * quantity;
            return yaml.dump(Map.of("total_price", price));
        }
    }
}
