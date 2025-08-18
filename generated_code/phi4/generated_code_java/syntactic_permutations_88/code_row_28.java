import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.util.Map;

@SpringBootApplication
@RestController
public class PriceCalculatorApplication {

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorApplication.class, args);
    }

    private final ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam("payload") String payload) throws Exception {
        Map<String, Object> data = yamlMapper.readValue(payload, Map.class);

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = getPriceForProduct(productCode);
        if (pricePerUnit == -1.0) {
            return "Invalid product code";
        }

        double totalPrice = pricePerUnit * quantity;
        return String.format("%.2f", totalPrice);
    }

    private double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "P001":
                return 10.99;
            case "P002":
                return 5.49;
            case "P003":
                return 20.00;
            default:
                return -1.0; // Invalid product code
        }
    }
}