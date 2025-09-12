import java.io.StringReader;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

public class PriceCalculatorMicroservice {

    private static Map<String, Double> priceMap = new HashMap<>();

    static {
        priceMap.put("A123", 19.99);
        priceMap.put("B456", 5.49);
        priceMap.put("C789", 33.75);
    }

    public void calculatePrice(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(new StringReader(yamlPayload));

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double totalPrice = get_price_for_product_code(productCode) * quantity;

        ObjectMapper mapper = new ObjectMapper();
        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        yaml.dump(result, response.getWriter());
    }

    private static double get_price_for_product_code(String productCode) {
        return priceMap.getOrDefault(productCode, 0.0);
    }
}