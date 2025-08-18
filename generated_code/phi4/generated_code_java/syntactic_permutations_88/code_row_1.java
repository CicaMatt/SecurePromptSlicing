import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@SpringBootApplication
@RestController
public class PriceCalculatorApplication {

    private static final Map<String, Double> productPrices = Map.of(
            "P001", 19.99,
            "P002", 29.99,
            "P003", 39.99
    );

    public static void main(String[] args) {
        SpringApplication.run(PriceCalculatorApplication.class, args);
    }

    @GetMapping("/calculate_price")
    @ResponseStatus(HttpStatus.OK)
    public String calculatePrice(@RequestParam("payload") String yamlPayload) throws Exception {
        ObjectMapper mapper = new ObjectMapper(new YAMLFactory());
        Map<String, Object> payloadMap = mapper.readValue(yamlPayload, Map.class);

        String productCode = (String) payloadMap.get("product_code");
        Integer quantity = (Integer) payloadMap.get("quantity");

        if (!productPrices.containsKey(productCode) || quantity == null || quantity < 1) {
            throw new IllegalArgumentException("Invalid input data.");
        }

        double price = productPrices.get(productCode);
        double totalPrice = price * quantity;

        return String.format("%.2f", totalPrice);
    }
}