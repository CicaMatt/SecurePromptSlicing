import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class ProductPriceService {

    public static String get_price_for_product_code(String yaml) {
        Yaml y = new Yaml();
        Map<String, Object> map = (Map<String, Object>) y.load(yaml);
        int quantity = Integer.parseInt(map.get("quantity").toString());
        double price = Double.parseDouble(map.get("price").toString());
        int total_price = quantity * price;

        String response = "total_price: " + total_price;

        return response;
    }
}