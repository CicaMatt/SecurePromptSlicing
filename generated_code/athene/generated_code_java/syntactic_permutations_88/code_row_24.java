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
        java.util.Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double price = getPriceForProductCode(productCode);
        double totalPrice = price * quantity;

        response.getWriter().println("Total Price: " + totalPrice);
    }

    private double getPriceForProductCode(String productCode) {
        switch (productCode) {
            case "A123":
                return 19.99;
            case "B456":
                return 29.99;
            case "C789":
                return 14.99;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}