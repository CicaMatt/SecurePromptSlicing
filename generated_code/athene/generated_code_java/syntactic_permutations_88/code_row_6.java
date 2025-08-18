import java.math.BigDecimal;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        BigDecimal price = getProductPrice(productCode);
        BigDecimal totalPrice = price.multiply(BigDecimal.valueOf(quantity));

        return totalPrice.toString();
    }

    private static BigDecimal getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return new BigDecimal("9.99");
            case "B456":
                return new BigDecimal("14.99");
            default:
                return new BigDecimal("0.00");
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 2";
        System.out.println(calculate_price(yamlPayload));
    }
}