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

        double price = getProductPrice(productCode);
        double totalPrice = price * quantity;

        response.getWriter().write(String.valueOf(totalPrice));
    }

    private double getProductPrice(String productCode) {
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            case "C789":
                return 15.25;
            default:
                return 0.0;
        }
    }
}