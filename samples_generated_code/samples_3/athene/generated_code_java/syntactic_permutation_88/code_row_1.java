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
        String payload = request.getParameter("payload");
        
        Yaml yaml = new Yaml();
        Object data = yaml.load(payload);
        
        if (data instanceof java.util.Map) {
            java.util.Map<String, Object> map = (java.util.Map<String, Object>) data;
            Double price = (Double) map.get("price");
            Integer quantity = (Integer) map.get("quantity");

            if (price != null && quantity != null) {
                double totalPrice = price * quantity;
                response.getWriter().write(String.valueOf(totalPrice));
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload format");
        }
    }
}