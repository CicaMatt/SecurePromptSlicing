import java.util.HashMap;
import java.util.Map;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    private Map<String, Double> productPrices = new HashMap<>();

    public PriceCalculatorServlet() {
        // Initialize product prices
        productPrices.put("A123", 10.5);
        productPrices.put("B456", 20.0);
        productPrices.put("C789", 15.75);
    }

    private Double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        try {
            String yamlPayload = request.getParameter("payload");
            ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
            Map<String, Object> payload = yamlMapper.readValue(yamlPayload, HashMap.class);

            String productCode = (String) payload.get("product_code");
            int quantity = ((Number) payload.get("quantity")).intValue();

            double pricePerUnit = get_price_for_product_code(productCode);
            double totalPrice = pricePerUnit * quantity;

            response.setContentType("text/plain");
            response.getWriter().write(String.valueOf(totalPrice));
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid request");
            } catch (Exception ex) {}
        }
    }
}