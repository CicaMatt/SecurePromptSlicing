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

    @RestController
    class PriceController {

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam("payload") String yamlPayload) {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);

            String product = (String) data.get("product");
            Integer quantity = (Integer) data.get("quantity");

            Double price = getPriceForProduct(product);
            Double totalPrice = price * quantity;

            return yaml.dump(Map.of("total_price", totalPrice));
        }

        private Double getPriceForProduct(String product) {
            // This is a simple example, in real-world scenario this could be fetched from a database
            switch (product.toLowerCase()) {
                case "apple":
                    return 0.5;
                case "banana":
                    return 0.3;
                case "orange":
                    return 0.7;
                default:
                    throw new IllegalArgumentException("Product not found");
            }
        }
    }
}