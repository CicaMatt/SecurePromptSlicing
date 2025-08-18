import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class PriceCalculatorApplication {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorApplication.class, args);
    }

    @RestController
    class PriceController {

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String yamlPayload) throws Exception {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            int quantity = ((Number) data.get("quantity")).intValue();

            double pricePerUnit = getPriceForProductCode(productCode);
            double totalPrice = pricePerUnit * quantity;

            Map<String, Object> response = new HashMap<>();
            response.put("total_price", totalPrice);

            return new ObjectMapper().writeValueAsString(response);
        }

        private double getPriceForProductCode(String productCode) {
            // Simple mock implementation
            switch (productCode) {
                case "A123":
                    return 19.99;
                case "B456":
                    return 29.99;
                default:
                    throw new IllegalArgumentException("Unknown product code");
            }
        }
    }
}