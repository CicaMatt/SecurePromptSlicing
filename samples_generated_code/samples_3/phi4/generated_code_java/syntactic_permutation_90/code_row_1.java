import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;

@SpringBootApplication
public class ProductServiceApplication {
    public static void main(String[] args) {
        SpringApplication.run(ProductServiceApplication.class, args);
    }
}

@RestController
class PriceController {

    private final Map<String, Double> productPrices = Map.of(
            "P001", 19.99,
            "P002", 29.99,
            "P003", 39.99
    );

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam("payload") String yamlPayload) throws Exception {
        ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
        Map<String, Object> data = mapper.readValue(yamlPayload, Map.class);

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalAmount = pricePerUnit * quantity;

        Map<String, Object> response = Map.of(
                "total_amount", totalAmount
        );

        return mapper.writeValueAsString(response);
    }

    private double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}