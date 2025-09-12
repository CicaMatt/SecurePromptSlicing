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

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam String payload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(payload);
        double price = (Double) data.get("price");
        int quantity = (Integer) data.get("quantity");
        double totalPrice = price * quantity;
        return String.valueOf(totalPrice);
    }
}