import org.yaml.snakeyaml.Yaml;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet("/calculate_price")
public class PriceServlet extends HttpServlet {
    private static final Map<String, Double> PRODUCT_PRICES = Map.of(
        "A123", 10.5,
        "B456", 20.75,
        "C789", 5.0
    );

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);
        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        double totalPrice = PRODUCT_PRICES.getOrDefault(productCode, 0.0) * quantity;
        response.getWriter().write(String.valueOf(totalPrice));
    }
}