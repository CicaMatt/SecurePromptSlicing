import java.util.HashMap;
import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    private double get_price_for_product_code(String productCode) {
        Map<String, Double> prices = new HashMap<>();
        prices.put("A123", 10.5);
        prices.put("B456", 20.0);
        prices.put("C789", 5.0);
        return prices.getOrDefault(productCode, 0.0);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getParameter("yaml");
        Yaml yaml = new Yaml();
        Map<String, Object> payload = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) payload.get("product_code");
        int quantity = (int) payload.get("quantity");

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        response.setContentType("application/x-yaml");
        PrintWriter out = response.getWriter();
        out.println(yaml.dump(result));
    }
}