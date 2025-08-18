import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.io.StringReader;
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
    public String calculatePrice(@RequestParam String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(new StringReader(yamlPayload));

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        Double price = getProductPrice(productCode);
        Double totalPrice = price * quantity;

        return String.valueOf(totalPrice);
    }

    private Double getProductPrice(String productCode) {
        // This is a placeholder for actual product price retrieval logic
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}