import java.io.IOException;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        ObjectMapper objectMapper = new ObjectMapper();

        try {
            @SuppressWarnings("unchecked")
            Object data = yaml.load(yamlPayload);
            double price = ((Number) data.toString().contains("price") ? 
                ((Number)((java.util.Map<String, Object>)data).get("price")).doubleValue() : 0.0);
            int quantity = ((Number) data.toString().contains("quantity") ? 
                ((Number)((java.util.Map<String, Object>)data).get("quantity")).intValue() : 1);

            double totalPrice = price * quantity;
            return String.valueOf(totalPrice);
        } catch (Exception e) {
            throw new RuntimeException("Error parsing YAML", e);
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "price: 10.5\nquantity: 3";
        System.out.println(calculate_price(yamlPayload));
    }
}