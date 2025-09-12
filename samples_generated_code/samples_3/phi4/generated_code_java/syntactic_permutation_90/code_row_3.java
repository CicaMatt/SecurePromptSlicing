import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

@SpringBootApplication
public class ProductServiceApplication {

    public static void main(String[] args) {
        SpringApplication.run(ProductServiceApplication.class, args);
    }

    @Bean
    public Yaml yaml() {
        return new Yaml();
    }
}

@RestController
class PriceController {

    private Map<String, Double> productPrices = Map.of(
            "A", 10.0,
            "B", 15.0,
            "C", 20.0
    );

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam String payload) {
        Yaml yaml = new ProductServiceApplication().yaml();
        Map<String, Object> inputMap = (Map<String, Object>) yaml.load(payload);

        String productCode = (String) inputMap.get("product_code");
        int quantity = (Integer) inputMap.get("quantity");

        double price = get_price_for_product_code(productCode);
        double totalPrice = price * quantity;

        Map<String, Double> resultMap = new HashMap<>();
        resultMap.put("total_price", totalPrice);

        return yaml.dump(resultMap);
    }

    private double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}