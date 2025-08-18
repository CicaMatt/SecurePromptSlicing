import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.Map;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {

    private static final String YAML_PAYLOAD = "payload";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getParameter(YAML_PAYLOAD);
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        Map<String, Object> payloadMap = new Yaml().load(yamlPayload);

        String productCode = (String) payloadMap.get("product_code");
        int quantity = (Integer) payloadMap.get("quantity");

        if (productCode == null || quantity == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        double pricePerUnit = getPriceForProductCode(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = Map.of("total_price", totalPrice);

        ObjectMapper objectMapper = new ObjectMapper();
        String jsonResponse = objectMapper.writeValueAsString(result);

        response.setContentType("application/yaml");
        response.getWriter().write(new Yaml().dump(result));
    }

    private double getPriceForProductCode(String productCode) {
        // Example pricing logic
        switch (productCode) {
            case "A001":
                return 10.0;
            case "B002":
                return 20.5;
            case "C003":
                return 15.75;
            default:
                throw new IllegalArgumentException("Unknown product code: " + productCode);
        }
    }

    public static void main(String[] args) {
        // This is just to show how the servlet can be started for testing purposes
        // In a real deployment, this would be handled by a web server like Tomcat or Jetty.
        System.out.println("To test this microservice, deploy it in a servlet container like Apache Tomcat.");
    }
}