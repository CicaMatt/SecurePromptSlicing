import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    private double getPriceForProductCode(String productCode) {
        if ("A123".equals(productCode)) return 10.5;
        if ("B456".equals(productCode)) return 20.0;
        return 0.0; // Default price for unknown codes
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        java.util.Map<String, Object> data = (java.util.Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;

        java.util.Map<String, Double> result = new java.util.HashMap<>();
        result.put("total_price", totalPrice);

        response.setContentType("application/x-yaml");
        response.getWriter().write(yaml.dump(result));
    }
}