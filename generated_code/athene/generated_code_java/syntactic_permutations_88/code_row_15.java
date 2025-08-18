import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static String calculate_price(HttpServletRequest request) {
        String payload = request.getParameter("payload");
        Map<String, Object> data = new Yaml().load(payload);
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = getPriceForProduct(productCode);
        double totalPrice = price * quantity;

        return String.valueOf(totalPrice);
    }

    private static double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            case "C789":
                return 15.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}