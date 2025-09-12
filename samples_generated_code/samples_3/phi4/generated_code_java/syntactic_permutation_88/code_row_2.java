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

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getQueryString();
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "YAML payload is required");
            return;
        }

        Map<String, Object> parsedData = parseYaml(yamlPayload);
        if (parsedData == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML format");
            return;
        }

        String productKey = (String) parsedData.get("product");
        Integer quantity = (Integer) parsedData.get("quantity");

        if (productKey == null || quantity == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "YAML must contain 'product' and 'quantity'");
            return;
        }

        double pricePerUnit = getProductPrice(productKey);
        if (pricePerUnit < 0) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Product not found");
            return;
        }

        double totalPrice = pricePerUnit * quantity;
        response.setContentType("text/plain");
        response.getWriter().write(String.valueOf(totalPrice));
    }

    private Map<String, Object> parseYaml(String yamlPayload) {
        Yaml yaml = new Yaml();
        try {
            return (Map<String, Object>) yaml.load(yamlPayload);
        } catch (Exception e) {
            return null;
        }
    }

    private double getProductPrice(String productKey) {
        // This is a simple example. In real applications, consider fetching from a database or service.
        switch (productKey.toLowerCase()) {
            case "apple":
                return 0.5;
            case "banana":
                return 0.3;
            case "orange":
                return 0.7;
            default:
                return -1;
        }
    }
}


To run this code, you need to set up a Java web server like Apache Tomcat and include the SnakeYAML library in your project dependencies. You can add SnakeYAML using Maven:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>2.0</version>
</dependency>


This code assumes you have a web server configured to handle servlets and that the `calculate_price` endpoint is mapped correctly.