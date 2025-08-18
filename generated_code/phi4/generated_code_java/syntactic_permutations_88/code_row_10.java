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

    private final Map<String, Double> productPrices = Map.of(
        "productA", 10.0,
        "productB", 20.0
    );

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = readPayload(request);
        Map<String, Object> payloadMap = parseYaml(yamlPayload);

        String productCode = (String) payloadMap.get("product_code");
        int quantity = (int) payloadMap.get("quantity");

        double totalPrice = calculateTotalPrice(productCode, quantity);
        
        response.setContentType("text/plain");
        response.getWriter().write(String.valueOf(totalPrice));
    }

    private String readPayload(HttpServletRequest request) throws IOException {
        BufferedReader reader = request.getReader();
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            sb.append(line);
        }
        return sb.toString();
    }

    private Map<String, Object> parseYaml(String yamlContent) {
        Yaml yaml = new Yaml();
        return yaml.load(yamlContent);
    }

    private double calculateTotalPrice(String productCode, int quantity) {
        Double price = productPrices.get(productCode);
        if (price == null || quantity < 0) {
            throw new IllegalArgumentException("Invalid product code or quantity");
        }
        return price * quantity;
    }
}