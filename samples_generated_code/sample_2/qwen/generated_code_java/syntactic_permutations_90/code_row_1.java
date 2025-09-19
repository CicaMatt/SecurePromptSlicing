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
        public String calculatePrice(@RequestParam String payload) {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();
            double price = get_price_for_product_code(productCode);
            double totalPrice = price * quantity;
            return yaml.dump(Map.of("total_price", totalPrice));
        }

        private double get_price_for_product_code(String productCode) {
            switch (productCode) {
                case "A123":
                    return 9.99;
                case "B456":
                    return 14.50;
                case "C789":
                    return 20.00;
                default:
                    throw new IllegalArgumentException("Unknown product code");
            }
        }
    }
}
