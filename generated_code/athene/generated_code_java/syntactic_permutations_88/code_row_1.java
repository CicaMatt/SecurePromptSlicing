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

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Object data = yaml.load(payload);
        
        if (data instanceof java.util.Map) {
            java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
            String productCode = (String) map.get("product_code");
            Integer quantity = (Integer) map.get("quantity");

            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;

            response.getWriter().write(String.valueOf(totalPrice));
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload format");
        }
    }

    private double getProductPrice(String productCode) {
        // Simple mock implementation
        if ("A".equals(productCode)) return 10.0;
        if ("B".equals(productCode)) return 20.0;
        if ("C".equals(productCode)) return 30.0;
        throw new IllegalArgumentException("Unknown product code: " + productCode);
    }
}