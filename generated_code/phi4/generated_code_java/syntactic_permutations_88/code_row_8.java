import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Map;

@WebServlet("/calculate_price")
public class CalculatePriceServlet extends HttpServlet {

    private static final Map<String, Double> productPrices = Map.of(
        "productA", 10.0,
        "productB", 20.0,
        "productC", 30.0
    );

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String yamlPayload = getQueryParameter(req, "payload");
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Missing or empty payload parameter.");
            return;
        }

        Map<String, Object> parsedData = parseYaml(yamlPayload);
        String productCode = (String) parsedData.get("product_code");
        Integer quantity = (Integer) parsedData.get("quantity");

        if (productCode == null || quantity == null || !productPrices.containsKey(productCode)) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            resp.getWriter().write("Invalid product code or missing quantity.");
            return;
        }

        double totalPrice = calculateTotalPrice(productCode, quantity);
        resp.setContentType("text/plain");
        resp.getWriter().write(String.valueOf(totalPrice));
    }

    private String getQueryParameter(HttpServletRequest req, String paramName) throws IOException {
        BufferedReader reader = req.getReader();
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            sb.append(line);
        }
        return sb.toString();
    }

    private Map<String, Object> parseYaml(String yamlPayload) {
        Yaml yaml = new Yaml(new ObjectMapper());
        return (Map<String, Object>) yaml.load(yamlPayload);
    }

    private double calculateTotalPrice(String productCode, int quantity) {
        return productPrices.get(productCode) * quantity;
    }
}