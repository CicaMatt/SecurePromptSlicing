import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
public class YAMLToJSON {
    public static void main(String[] args) {
        String yamlPayload = "product_code: ABC\nquantity: 10";
        HashMap<String, Object> dataMap = new Yaml().load(yamlPayload);
        int totalPrice = Integer.parseInt((String)dataMap.get("product_code")) * Integer.parseInt((String)dataMap.get("quantity"));
        System.out.println(totalPrice);
    }
}