import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.Map;

@SpringBootApplication
public class MicroserviceApplication {

    public static void main(String[] args) {
        SpringApplication.run(MicroserviceApplication.class, args);
    }

    @RestController
    class PriceController {

        private final Yaml yaml = new Yaml();
        private final ObjectMapper objectMapper = new ObjectMapper();

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String payload) throws IOException {
            Map<String, Object> map = yaml.load(payload);
            String productCode = (String) map.get("product_code");
            Integer quantity = (Integer) map.get("quantity");

            Double price = get_price_for_product_code(productCode);
            double totalPrice = price * quantity;

            return objectMapper.writeValueAsString(Map.of("total_price", totalPrice));
        }

        private Double get_price_for_product_code(String productCode) {
            // Example pricing logic
            switch (productCode) {
                case "A1":
                    return 10.99;
                case "B2":
                    return 5.49;
                default:
                    return 0.0;
            }
        }
    }
}
