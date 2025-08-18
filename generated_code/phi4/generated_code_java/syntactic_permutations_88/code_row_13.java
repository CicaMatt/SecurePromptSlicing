import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.Map;

public class PriceCalculatorAPI {

    public static void main(String[] args) {
        String yamlPayload = "{product_code: '123', quantity: 2}";
        try {
            System.out.println(calculatePrice(yamlPayload));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String calculatePrice(String yamlPayload) throws IOException {
        Yaml yaml = new Yaml(new ObjectMapper());
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (Integer) data.get("quantity");

        double price = getPriceForProduct(productCode);
        double totalPrice = price * quantity;

        return String.format("%.2f", totalPrice);
    }

    private static double getPriceForProduct(String productCode) {
        // Example pricing logic
        switch (productCode) {
            case "123":
                return 9.99;
            default:
                return 0.0; // Unknown product
        }
    }
}


To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.14.0</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>