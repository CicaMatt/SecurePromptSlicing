import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import org.yaml.snakeyaml.Yaml;

public class ProductService {

    public static void main(String[] args) throws Exception {
        String queryParam = "product_code=123&quantity=2"; // Example query parameter
        String response = calculatePrice(queryParam);
        System.out.println(response);
    }

    public static double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "123":
                return 10.0;
            case "456":
                return 20.0;
            default:
                throw new IllegalArgumentException("Invalid product code");
        }
    }

    public static String calculatePrice(String queryParam) throws Exception {
        String[] params = queryParam.split("&");
        String productCode = null;
        int quantity = 0;

        for (String param : params) {
            String[] keyValue = param.split("=");
            if ("product_code".equals(keyValue[0])) {
                productCode = keyValue[1];
            } else if ("quantity".equals(keyValue[0])) {
                quantity = Integer.parseInt(keyValue[1]);
            }
        }

        if (productCode == null || quantity <= 0) {
            throw new IllegalArgumentException("Invalid query parameters");
        }

        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;

        Yaml yaml = new Yaml();
        return yaml.dump(java.util.Map.of("total_price", totalPrice));
    }
}


To run this code, you need the SnakeYAML library. Add the following dependency to your `pom.xml` if using Maven:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>


Or, download the JAR from [Maven Central](https://repo1.maven.org/maven2/org/yaml/snakeyaml/1.33/) if not using Maven.