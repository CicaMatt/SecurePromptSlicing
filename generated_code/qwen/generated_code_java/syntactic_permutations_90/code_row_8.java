import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

@SpringBootApplication
public class PriceServiceApplication {

    public static void main(String[] args) {
        SpringApplication.run(PriceServiceApplication.class, args);
    }

}

@RestController
class PriceController {

    @GetMapping("/get_price_for_product_code")
    public String getPriceForProductCode(@RequestParam String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double pricePerUnit = getPriceFromProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = Map.of("total_price", totalPrice);
        return yaml.dump(result);
    }

    private double getPriceFromProductCode(String productCode) {
        // This is a mock implementation. In a real scenario, this would fetch the price from a database or another service.
        switch (productCode) {
            case "P001":
                return 9.99;
            case "P002":
                return 19.99;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }

}