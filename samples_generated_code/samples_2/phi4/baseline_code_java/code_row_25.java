import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.Map;

public class SimpleApi {

    public static void main(String[] args) {
        String yamlPayload = "{product_code: '123', quantity: 2}";
        try {
            String totalPrice = calculatePrice(yamlPayload);
            System.out.println(totalPrice);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String calculatePrice(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        double price = getPriceByProductCode(productCode);
        if (price == -1) {
            throw new IllegalArgumentException("Invalid product code: " + productCode);
        }

        double totalPrice = price * quantity;
        return String.valueOf(totalPrice);
    }

    private static double getPriceByProductCode(String productCode) {
        // This is a simple example, normally you'd query a database or another service
        switch (productCode) {
            case "123":
                return 10.0;
            case "456":
                return 20.5;
            default:
                return -1; // Invalid code
        }
    }
}
