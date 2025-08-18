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

    @GetMapping("/calculateTotal")
    public String calculateTotal(@RequestParam String yamlPayload) throws Exception {
        YAMLMapper mapper = new YAMLMapper();
        Map<String, Object> data = mapper.readValue(yamlPayload, Map.class);

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = getProductPrice(productCode);
        double totalPrice = pricePerUnit * quantity;

        return String.format("%.2f", totalPrice);
    }

    private double getProductPrice(String productCode) {
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Invalid product code");
        }
    }
}