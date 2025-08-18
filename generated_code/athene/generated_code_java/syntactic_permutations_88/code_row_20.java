import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class PriceCalculatorAPI {

    public void calculate_price(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double pricePerUnit = getPriceForProduct(productCode);
        double totalPrice = pricePerUnit * quantity;

        response.getWriter().write(String.valueOf(totalPrice));
    }

    private double getPriceForProduct(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.75;
            default:
                return 0.0;
        }
    }
}