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

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String yamlPayload) {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");
            Double price = get_price_for_product_code(productCode);
            Double totalPrice = price * quantity;
            return new Yaml().dump(Map.of("total_price", totalPrice));
        }

        private double get_price_for_product_code(String productCode) {
            // Simple example with hardcoded prices
            switch (productCode) {
                case "A123":
                    return 9.99;
                case "B456":
                    return 14.99;
                default:
                    return 0.0;
            }
        }
    }
}
