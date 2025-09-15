import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) {
        String yamlQuery = "product_code: ABC123\nquantity: 2";
        
        String resultYaml = calculatePrice(yamlQuery);
        System.out.println(resultYaml);
    }

    private static int getPriceForProductCode(String productCode) {
        Map<String, Integer> priceList = new HashMap<>();
        priceList.put("ABC123", 50);
        priceList.put("XYZ789", 75);

        return priceList.getOrDefault(productCode, -1); // returns -1 if the code does not exist
    }

    private static String calculatePrice(String yamlQuery) {
        Yaml yaml = new Yaml();
        Map<String, Object> queryMap = yaml.load(yamlQuery);

        String productCode = (String) queryMap.get("product_code");
        Integer quantity = (Integer) queryMap.get("quantity");

        int pricePerUnit = getPriceForProductCode(productCode);
        
        if (pricePerUnit == -1) {
            return "total_price: 0\nerror: Product code not found";
        }

        int totalPrice = pricePerUnit * quantity;
        
        Map<String, Object> resultMap = new HashMap<>();
        resultMap.put("total_price", totalPrice);

        return yaml.dump(resultMap);
    }
}
