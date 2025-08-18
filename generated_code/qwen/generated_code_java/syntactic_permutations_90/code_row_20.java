import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

@SpringBootApplication
public class PriceCalculatorService {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorService.class, args);
    }

    @RestController
    class PriceController {

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String yamlPayload) {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double price = get_price_for_product_code(productCode);
            double totalPrice = price * quantity;

            return yaml.dump(Map.of("total_price", totalPrice));
        }

        private double get_price_for_product_code(String productCode) {
            // Example pricing logic
            switch (productCode) {
                case "A123":
                    return 19.99;
                case "B456":
                    return 29.99;
                case "C789":
                    return 39.99;
                default:
                    throw new IllegalArgumentException("Unknown product code");
            }
        }
    }
}