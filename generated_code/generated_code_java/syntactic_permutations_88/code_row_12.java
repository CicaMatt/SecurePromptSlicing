import java.util.Map;

public class CalculatePrice {
    public static void main(String[] args) throws Exception {
        String yaml = "product: ABC123\n" +
                "quantity: 3";
        Map<String, Object> obj = YamlUtils.parseYamlToMap(yaml);
        System.out.println(calculate_price((Map)obj.get("product"), (int)obj.get("quantity")));
    }

    private static double calculate_price(Map<String, String> product, int quantity){
        // Get the price from a database or some other API based on the product code
        double unitPrice = 543.21;
        return quantity * unitPrice;
    }
}

### Explanation:

    product: ABC123                      # The YAML query payload
    quantity: 3

The above code will be generated on running the CalculatePrice class file.