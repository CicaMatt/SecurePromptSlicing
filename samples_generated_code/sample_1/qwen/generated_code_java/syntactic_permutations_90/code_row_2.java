import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.io.InputStream;
import java.util.Map;

@SpringBootApplication
public class PriceCalculatorApplication {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorApplication.class, args);
    }

    @RestController
    class PriceController {

        private final Yaml yaml = new Yaml();

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String payload) {
            Map<String, Object> data = yaml.load(payload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();
            double totalPrice = get_price_for_product_code(productCode) * quantity;
            return yaml.dump(Map.of("total_price", totalPrice));
        }

        private double get_price_for_product_code(String productCode) {
            // This is a simple example, in real world this could be fetched from a database
            switch (productCode) {
                case "A001":
                    return 19.99;
                case "B002":
                    return 5.49;
                default:
                    throw new IllegalArgumentException("Unknown product code");
            }
        }
    }
}