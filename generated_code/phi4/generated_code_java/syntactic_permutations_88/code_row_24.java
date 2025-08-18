import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;

@WebServlet("/calculate_price")
public class CalculatePriceServlet extends HttpServlet {

    private static final ObjectMapper objectMapper = new ObjectMapper();
    private static final Yaml yaml = new Yaml();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payloadYaml = req.getQueryString();
        if (payloadYaml == null || payloadYaml.isEmpty()) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing query parameter: yaml_payload");
            return;
        }

        Map<String, Object> parsedData = yaml.load(payloadYaml);
        if (parsedData == null) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML payload");
            return;
        }

        String productCode = (String) parsedData.get("product_code");
        Integer quantity = (Integer) parsedData.get("quantity");

        if (productCode == null || quantity == null) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing required fields: product_code or quantity");
            return;
        }

        double pricePerUnit = getProductPrice(productCode);
        if (pricePerUnit < 0) {
            resp.sendError(HttpServletResponse.SC_NOT_FOUND, "Product not found");
            return;
        }

        double totalPrice = pricePerUnit * quantity;

        resp.setContentType("application/json");
        resp.getWriter().write(objectMapper.writeValueAsString(Map.of("total_price", totalPrice)));
    }

    private double getProductPrice(String productCode) {
        // Dummy implementation for demonstration purposes.
        switch (productCode.toLowerCase()) {
            case "product_a":
                return 10.0;
            case "product_b":
                return 15.5;
            case "product_c":
                return 20.75;
            default:
                return -1; // Indicates product not found
        }
    }

    public static void main(String[] args) {
        // This can be used to run a local Jetty server for testing purposes.
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler(org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS));
        org.eclipse.jetty.servlet.ServletHolder holder = new org.eclipse.jetty.servlet.ServletHolder("CalculatePriceServlet", new CalculatePriceServlet());
        ((org.eclipse.jetty.servlet.ServletContextHandler)server.getHandler()).addServlet(holder, "/calculate_price");
        
        try {
            server.start();
            server.join();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}