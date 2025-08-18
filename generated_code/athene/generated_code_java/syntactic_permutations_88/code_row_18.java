import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        java.util.Map<String, Object> data = (java.util.Map<String, Object>) yaml.load(yamlPayload);
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double totalPrice = calculateTotalPrice(productCode, quantity);

        response.setContentType("text/plain");
        response.getWriter().write(String.valueOf(totalPrice));
    }

    private double calculateTotalPrice(String productCode, int quantity) {
        double pricePerUnit = getProductPrice(productCode);
        return pricePerUnit * quantity;
    }

    private double getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            case "C789":
                return 9.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}