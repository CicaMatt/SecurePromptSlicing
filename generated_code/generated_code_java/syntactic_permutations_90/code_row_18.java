import org.springframework.web.bind.annotation.*;

@RestController
public class CalculatePrice {
    private static Map<String, Integer> productCodeToPrice = new HashMap<>();
    static {
        productCodeToPrice.put("A", 50);
        productCodeToPrice.put("B", 30);
        productCodeToPrice.put("C", 20);
        productCodeToPrice.put("D", 15);
    }

    @GetMapping("/calculate-price")
    public Integer calculatePrice(@RequestParam String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        return getPriceForProductCode((String) data.get("product_code")) * (int) data.get("quantity");
    }

    private int getPriceForProductCode(String productCode) {
        if (!productCodeToPrice.containsKey(productCode)) {
            return 0;
        }
        return productCodeToPrice.get(productCode);
    }
}