import java.util.Map;
import org.yaml.snakeyaml.Yaml;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = (int) data.get("quantity");

        double totalPrice = calculatePrice(productCode, quantity);

        response.setContentType("application/x-yaml");
        PrintWriter out = response.getWriter();
        out.println(yaml.dump(Map.of("total_price", totalPrice)));
    }

    private double get_price_for_product_code(String productCode) {
        // Dummy pricing logic
        switch (productCode) {
            case "A123":
                return 10.5;
            case "B456":
                return 20.0;
            default:
                return 0.0;
        }
    }

    private double calculatePrice(String productCode, int quantity) {
        return get_price_for_product_code(productCode) * quantity;
    }
}