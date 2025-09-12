import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorAPI {

    public static String calculate_price(String yamlPayload) {
        Yaml yaml = new Yaml();
        Object data = yaml.load(yamlPayload);
        if (data instanceof java.util.Map) {
            java.util.Map<String, Object> mapData = (java.util.Map<String, Object>) data;
            String productCode = (String) mapData.get("product_code");
            Integer quantity = (Integer) mapData.get("quantity");

            double pricePerUnit = getProductPrice(productCode);
            double totalPrice = pricePerUnit * quantity;

            return Double.toString(totalPrice);
        }
        return "Invalid input";
    }

    private static double getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.95;
            case "C789":
                return 5.25;
            default:
                return 0.0;
        }
    }

    public static void main(String[] args) {
        String yamlPayload = "product_code: A123\nquantity: 2";
        System.out.println(calculate_price(yamlPayload));
    }
}