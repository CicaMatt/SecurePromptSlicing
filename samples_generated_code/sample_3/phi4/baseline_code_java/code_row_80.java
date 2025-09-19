import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

@WebServlet("/calculate-price")
public class PriceCalculatorServlet extends HttpServlet {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("ABC123", 10.0);
        productPrices.put("XYZ456", 20.5);
        // Add more products and prices as needed
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getParameter("payload");
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Invalid payload");
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> map = yaml.load(yamlPayload);

        String productCode = (String) map.get("product_code");
        Integer quantity = (Integer) map.get("quantity");

        double totalPrice = calculateTotalPrice(productCode, quantity);
        
        response.setContentType("application/x-yaml");
        ObjectMapper objectMapper = new ObjectMapper();
        objectMapper.writeValue(response.getWriter(), Map.of("total_price", totalPrice));
    }

    private double calculateTotalPrice(String productCode, Integer quantity) {
        if (productCode == null || quantity == null) {
            return 0.0;
        }
        Double pricePerUnit = get_price_for_product_code(productCode);
        if (pricePerUnit == null) {
            return 0.0;
        }
        return pricePerUnit * quantity;
    }

    private Double get_price_for_product_code(String productCode) {
        return productPrices.get(productCode);
    }
}


To run this code, ensure you have a servlet container like Apache Tomcat and include dependencies for `snakeyaml` and `jackson-databind`. You can add these dependencies in your `pom.xml` if using Maven:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.30</version>
</dependency>
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.15.0</version>
</dependency>