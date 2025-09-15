import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class MicroserviceApplication {

    public static void main(String[] args) {
        SpringApplication.run(MicroserviceApplication.class, args);
    }

    @RestController
    class PriceController {

        private final Map<String, Double> productPrices = new HashMap<>() {{
            put("A123", 19.99);
            put("B456", 29.99);
            put("C789", 39.99);
        }};

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String yamlPayload) {
            Yaml yaml = new Yaml();
            Map<String, Integer> items = yaml.load(yamlPayload);

            double totalPrice = 0.0;
            for (Map.Entry<String, Integer> entry : items.entrySet()) {
                String productCode = entry.getKey();
                int quantity = entry.getValue();
                Double price = get_price_for_product_code(productCode);
                if (price != null) {
                    totalPrice += price * quantity;
                }
            }

            Map<String, Double> response = new HashMap<>();
            response.put("totalPrice", totalPrice);
            return yaml.dump(response);
        }

        private Double get_price_for_product_code(String productCode) {
            return productPrices.get(productCode);
        }
    }
}
