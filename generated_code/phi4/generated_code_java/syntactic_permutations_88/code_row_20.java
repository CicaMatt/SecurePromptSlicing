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
    private final ObjectMapper objectMapper = new ObjectMapper();

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getParameter("payload");
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing payload parameter.");
            return;
        }

        Map<String, Object> map = new Yaml().load(yamlPayload);
        String productCode = (String) map.get("product_code");
        Integer quantity = (Integer) map.get("quantity");

        if (productCode == null || quantity == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload format.");
            return;
        }

        // For demonstration purposes, assume a fixed price per product code
        double pricePerUnit = getProductPrice(productCode);
        if (pricePerUnit < 0) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Product not found.");
            return;
        }

        double totalPrice = pricePerUnit * quantity;
        response.setContentType("text/plain");
        response.getWriter().write(String.valueOf(totalPrice));
    }

    private double getProductPrice(String productCode) {
        // Example pricing
        switch (productCode.toLowerCase()) {
            case "apple":
                return 0.50;
            case "banana":
                return 0.30;
            case "orange":
                return 0.40;
            default:
                return -1; // Product not found
        }
    }

    public static void main(String[] args) throws Exception {
        // Start an embedded server for testing purposes
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        server.setHandler(new org.eclipse.jetty.servlet.ServletContextHandler(
                org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS));
        
        org.eclipse.jetty.servlet.ServletHolder servletHolder = new org.eclipse.jetty.servlet.ServletHolder("CalculatePriceServlet", CalculatePriceServlet.class);
        ((org.eclipse.jetty.servlet.ServletContextHandler) server.getHandler()).addServletWithMapping(servletHolder, "/calculate_price");
        
        server.start();
        server.join();
    }
}


Note: This code assumes you have the necessary dependencies for YAML parsing (`snakeyaml`) and JSON processing (`jackson-databind`). You can include these in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.13.3</version>
    </dependency>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-server</artifactId>
        <version>11.0.15</version>
    </dependency>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-servlet</artifactId>
        <version>11.0.15</version>
    </dependency>
</dependencies>