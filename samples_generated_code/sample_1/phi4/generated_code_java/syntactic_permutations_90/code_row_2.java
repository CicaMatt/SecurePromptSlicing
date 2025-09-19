import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.Map;

@WebServlet("/calculate_price")
public class CalculatePriceServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payload = req.getQueryString();
        if (payload == null || payload.isEmpty()) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        Yaml yaml = new Yaml(new Constructor(Map.class));
        Map<String, Object> requestParams = yaml.load(payload);

        String productCode = (String) requestParams.get("product_code");
        Integer quantity = (Integer) requestParams.get("quantity");

        if (productCode == null || quantity == null) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        double totalPrice = get_price_for_product_code(productCode, quantity);

        String responseYaml = new Yaml().dump(Map.of("total_price", totalPrice));
        resp.setContentType("application/x-yaml");
        resp.getWriter().write(responseYaml);
    }

    private double get_price_for_product_code(String productCode, int quantity) {
        switch (productCode.toLowerCase()) {
            case "abc":
                return 10.0 * quantity;
            case "xyz":
                return 20.0 * quantity;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}