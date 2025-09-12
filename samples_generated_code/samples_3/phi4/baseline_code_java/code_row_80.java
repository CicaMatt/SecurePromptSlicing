import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

public class PriceCalculatorServlet extends HttpServlet {

    private static final ObjectMapper objectMapper = new ObjectMapper();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String yamlPayload = req.getQueryString();
        
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Invalid payload");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        if (productCode == null || quantity == null) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Missing product code or quantity");
            return;
        }

        double price = getProductPrice(productCode);

        if (price < 0) {
            resp.setStatus(HttpServletResponse.SC_NOT_FOUND);
            resp.getWriter().write("Product not found");
            return;
        }

        double totalPrice = price * quantity;

        resp.setContentType("text/plain");
        resp.getWriter().write(String.valueOf(totalPrice));
    }

    private double getProductPrice(String productCode) {
        // Dummy implementation, replace with actual logic to get product price
        Map<String, Double> productPrices = Map.of(
            "A001", 10.0,
            "B002", 15.5,
            "C003", 7.75
        );

        return productPrices.getOrDefault(productCode, -1);
    }

    public static void main(String[] args) {
        // This is just a placeholder for running the servlet in an actual server environment.
        // In practice, you would deploy this servlet to a web application server like Tomcat or Jetty.
    }
}