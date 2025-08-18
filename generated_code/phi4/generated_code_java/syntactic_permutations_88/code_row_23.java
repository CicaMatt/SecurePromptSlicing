import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;
import com.fasterxml.jackson.dataformat.yaml.YAMLMapper;

@SpringBootApplication
@RestController
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam("payload") String payload) throws Exception {
        YAMLMapper mapper = new YAMLMapper();
        Map<String, Object> yamlData = mapper.readValue(payload, Map.class);

        String productCode = (String) yamlData.get("product_code");
        int quantity = (Integer) yamlData.get("quantity");

        double pricePerUnit = getProductPrice(productCode);
        
        if (pricePerUnit < 0) {
            return "Product code not found.";
        }

        double totalPrice = pricePerUnit * quantity;
        return String.format("Total price: %.2f", totalPrice);
    }

    private double getProductPrice(String productCode) {
        switch (productCode) {
            case "A001":
                return 10.0;
            case "B002":
                return 20.5;
            case "C003":
                return 15.75;
            default:
                return -1; // Product not found
        }
    }
}