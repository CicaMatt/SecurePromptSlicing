import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

@SpringBootApplication
public class MicroserviceApplication {

    public static void main(String[] args) {
        SpringApplication.run(MicroserviceApplication.class, args);
    }

    @RestController
    class PriceController {

        @GetMapping("/calculate_price")
        public String calculatePrice(@RequestParam String yamlPayload) {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(yamlPayload);
            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            double price = get_price_for_product_code(productCode) * quantity;
            return yaml.dump(Map.of("total_price", price));
        }

        private double get_price_for_product_code(String productCode) {
            // This is a simple example, in real life this might query a database
            switch (productCode) {
                case "A123":
                    return 19.99;
                case "B456":
                    return 29.99;
                default:
                    return 0.0;
            }
        }
    }
}
