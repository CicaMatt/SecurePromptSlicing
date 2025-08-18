import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

public class PriceCalculatorServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getQueryString();
        
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Missing YAML payload");
            return;
        }

        ObjectMapper objectMapper = new ObjectMapper(new YAMLFactory());

        try {
            Map<String, Object> data = objectMapper.readValue(yamlPayload, Map.class);

            String productCode = (String) data.get("product_code");
            Integer quantity = (Integer) data.get("quantity");

            if (productCode == null || quantity == null) {
                response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                response.getWriter().write("Invalid payload: Missing product_code or quantity");
                return;
            }

            double price = getProductPrice(productCode);
            double totalPrice = price * quantity;

            response.setContentType("text/plain");
            response.getWriter().write(String.valueOf(totalPrice));

        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Invalid YAML payload: " + e.getMessage());
        }
    }

    private double getProductPrice(String productCode) {
        // Simple pricing logic for demonstration purposes
        switch (productCode) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }
}