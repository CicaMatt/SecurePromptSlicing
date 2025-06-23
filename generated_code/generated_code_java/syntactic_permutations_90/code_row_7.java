import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class ProductPriceCalculator {
    public static void main(String[] args) {
        String yamlPayload = "code: 1234\nquantity: 5";
        Map<String, Object> productInfo = (Map<String, Object>) new Yaml().load(yamlPayload);
        Integer quantity = (Integer) productInfo.get("quantity");
        Integer code = (Integer) productInfo.get("code");
        Double price = calculatePrice(code, quantity);
        String payload = "total_price: " + price;
        System.out.println(payload);
    }

    public static Double calculatePrice(int code, int quantity) {
        // this is where the actual price calculation would take place
        // for now we just return a dummy value of 99.99
        return 99.99;
    }
}