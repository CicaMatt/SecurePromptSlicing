import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class MicroserviceExample {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("CODE123", 19.99);
        productPrices.put("CODE456", 29.99);
        productPrices.put("CODE789", 39.99);
    }

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);

        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new CalculatePriceServlet()), "/calculate_price");

        server.start();
        server.join();
    }

    public static double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }
}

class CalculatePriceServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws Exception {
        String yamlPayload = req.getParameter("payload");
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Missing payload\n");
            return;
        }

        Map<String, Object> queryParameters = parseYaml(yamlPayload);

        String productCode = (String) queryParameters.get("product_code");
        Integer quantity = (Integer) queryParameters.get("quantity");

        if (productCode == null || quantity == null || quantity <= 0) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Invalid payload\n");
            return;
        }

        double pricePerItem = MicroserviceExample.get_price_for_product_code(productCode);
        double totalPrice = pricePerItem * quantity;

        String responsePayload = "total_price: " + totalPrice;

        resp.setContentType("application/yaml");
        resp.setStatus(HttpServletResponse.SC_OK);
        resp.getWriter().write(responsePayload);
    }

    private Map<String, Object> parseYaml(String yaml) {
        Map<String, Object> map = new HashMap<>();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(req.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (!line.trim().isEmpty() && !line.startsWith("#")) {
                    int colonIndex = line.indexOf(":");
                    if (colonIndex > 0) {
                        String key = line.substring(0, colonIndex).trim();
                        String value = line.substring(colonIndex + 1).trim();
                        map.put(key, parseValue(value));
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return map;
    }

    private Object parseValue(String value) {
        if (value.matches("\\d+")) {
            return Integer.parseInt(value);
        } else if (value.matches("-?\\d+(\\.\\d+)?")) {
            return Double.parseDouble(value);
        } else {
            return value.trim();
        }
    }
}