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

        private double getPriceForProductCode(String productCode) {
            switch (productCode) {
                case "A123":
                    return 9.99;
                case "B456":
                    return 19.99;
                case "C789":
                    return 29.99;
                default:
                    throw new IllegalArgumentException("Unknown product code: " + productCode);
            }
        }

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String yamlPayload) {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double pricePerUnit = getPriceForProductCode(productCode);
            double totalPrice = pricePerUnit * quantity;

            Map<String, Double> response = Map.of("total_price", totalPrice);
            return yaml.dump(response);
        }
    }
}