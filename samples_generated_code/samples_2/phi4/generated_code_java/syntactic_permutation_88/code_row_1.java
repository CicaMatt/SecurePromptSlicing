import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import com.fasterxml.jackson.dataformat.yaml.YAMLMapper;

@SpringBootApplication
@RestController
public class PricingApplication {

    public static void main(String[] args) {
        SpringApplication.run(PricingApplication.class, args);
    }

    private static final YAMLMapper yamlMapper = new YAMLMapper();

    @GetMapping("/calculate_price")
    public String calculatePrice(@RequestParam("payload") String payload) {
        try {
            PriceData data = yamlMapper.readValue(payload, PriceData.class);
            int pricePerUnit = 10; // Assume a fixed price per unit for simplicity
            int totalPrice = pricePerUnit * data.getQuantity();
            return Integer.toString(totalPrice);
        } catch (Exception e) {
            return "Error processing request: " + e.getMessage();
        }
    }

    private static class PriceData {
        private String code;
        private int quantity;

        public String getCode() {
            return code;
        }

        public void setCode(String code) {
            this.code = code;
        }

        public int getQuantity() {
            return quantity;
        }

        public void setQuantity(int quantity) {
            this.quantity = quantity;
        }
    }
}