import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Object data = yaml.load(yamlPayload);
        
        if (data instanceof java.util.Map) {
            @SuppressWarnings("unchecked")
            java.util.Map<String, Object> payload = (java.util.Map<String, Object>) data;
            String productCode = (String) payload.get("product_code");
            int quantity = ((Number) payload.get("quantity")).intValue();

            double totalPrice = calculatePrice(productCode, quantity);
            response.getWriter().write(Double.toString(totalPrice));
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML payload");
        }
    }

    private double calculatePrice(String productCode, int quantity) {
        // Mock pricing data
        java.util.Map<String, Double> prices = new java.util.HashMap<>();
        prices.put("A123", 10.5);
        prices.put("B456", 20.0);
        prices.put("C789", 15.75);

        double pricePerUnit = prices.getOrDefault(productCode, 0.0);
        return pricePerUnit * quantity;
    }
}