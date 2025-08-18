import java.io.IOException;
import java.util.Map;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

public class PriceService extends HttpServlet {

    private double get_price_for_product_code(String productCode) {
        // Mock price for demonstration
        if ("A123".equals(productCode)) return 9.99;
        else if ("B456".equals(productCode)) return 19.99;
        else if ("C789".equals(productCode)) return 29.99;
        return 0.0; // Default price
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> payload = yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = Map.of("total_price", totalPrice);
        String yamlResult = new Yaml().dump(result);

        response.setContentType("application/x-yaml");
        response.getWriter().write(yamlResult);
    }
}