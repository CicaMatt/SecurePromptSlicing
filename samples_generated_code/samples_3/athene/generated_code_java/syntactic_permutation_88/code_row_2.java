import java.io.IOException;
import java.util.Map;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);

        double price = ((Number) data.get("product_price")).doubleValue();
        int quantity = ((Number) data.get("quantity")).intValue();

        double totalPrice = price * quantity;
        response.getWriter().write(String.valueOf(totalPrice));
    }
}