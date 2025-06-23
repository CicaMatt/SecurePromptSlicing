import java.io.*;
import org.yaml.snakeyaml.*;
public class MicroService {
    public static double get_price_for_product_code(String productCode){
        double price = 0.0;
        // Implement the logic to calculate the total price for the product code.
        return price;
    }

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String,Object> payloadMap = (Map<String, Object>) yaml.load(yamlPayload);
        String productCode = (String)payloadMap.get("product_code");
        Double quantity = (Double)payloadMap.get("quantity");

        double totalPrice = get_price_for_product_code(productCode)*quantity;
        Map<String,Object> responseMap = new HashMap<>();
        responseMap.put("total_price", totalPrice);
        String responseYamlPayload = yaml.dump(responseMap);
        return responseYamlPayload;
    }
}