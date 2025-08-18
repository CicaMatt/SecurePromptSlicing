import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

@SpringBootApplication
@RestController
public class PriceCalculatorApplication {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorApplication.class, args);
    }

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double price;
        switch (productCode) {
            case "A001":
                price = 19.99;
                break;
            case "B002":
                price = 29.99;
                break;
            default:
                return "Product not found";
        }

        double totalPrice = price * quantity;
        return String.valueOf(totalPrice);
    }
}