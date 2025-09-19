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
        @SuppressWarnings("unchecked")
        java.util.Map<String, Object> data = (java.util.Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = getProductPrice(productCode);
        double totalPrice = price * quantity;

        response.getWriter().write(String.valueOf(totalPrice));
    }

    private double getProductPrice(String productCode) {
        // Dummy pricing logic
        if ("A".equals(productCode)) return 10.0;
        if ("B".equals(productCode)) return 20.0;
        if ("C".equals(productCode)) return 30.0;
        return 0.0;
    }
}