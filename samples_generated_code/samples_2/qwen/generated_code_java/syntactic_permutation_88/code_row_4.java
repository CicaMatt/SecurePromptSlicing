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
}

@RestController
class PriceController {

    private final Map<String, Double> priceMap = Map.of(
            "A001", 19.99,
            "B002", 5.49,
            "C003", 3.75
    );

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double price = priceMap.getOrDefault(productCode, 0.0);
        double totalPrice = price * quantity;

        return String.valueOf(totalPrice);
    }
}