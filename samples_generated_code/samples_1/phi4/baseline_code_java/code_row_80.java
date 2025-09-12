import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class ProductService {

    private static final Map<String, Double> productPrices = new HashMap<>();
    
    static {
        // Initialize with some dummy data
        productPrices.put("ABC123", 10.0);
        productPrices.put("XYZ789", 20.0);
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    public static String calculate_price(String yamlPayload) throws IOException {
        ObjectMapper mapper = new ObjectMapper();
        Map<String, Object> inputMap = mapper.readValue(yamlPayload, HashMap.class);

        String productCode = (String) inputMap.get("product_code");
        int quantity = (int) inputMap.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        DumperOptions options = new DumperOptions();
        options.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
        Yaml yaml = new Yaml(options);
        
        return yaml.dump(result);
    }

    public static void main(String[] args) {
        try {
            String inputYaml = "{ \"product_code\": \"ABC123\", \"quantity\": 3 }";
            String outputYaml = calculate_price(inputYaml);
            System.out.println(outputYaml);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}