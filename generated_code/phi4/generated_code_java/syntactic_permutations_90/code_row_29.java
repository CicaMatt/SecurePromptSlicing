import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {

    private static final Map<String, Double> productPrices = Map.of(
        "P001", 10.0,
        "P002", 20.5,
        "P003", 15.75
    );

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getParameter("payload");
        if (yamlPayload != null && !yamlPayload.isEmpty()) {
            Yaml yaml = new Yaml(new Constructor(Map.class));
            Map<String, Object> data = yaml.load(yamlPayload);

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            double totalPrice = calculateTotalPrice(productCode, quantity);
            Map<String, Double> result = Map.of("total_price", totalPrice);

            response.setContentType("application/x-yaml");
            yaml.dump(result, response.getWriter());
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing or empty payload.");
        }
    }

    private double calculateTotalPrice(String productCode, Integer quantity) {
        if (productCode == null || !productPrices.containsKey(productCode) || quantity == null) {
            return 0.0;
        }
        return productPrices.get(productCode) * quantity;
    }
}