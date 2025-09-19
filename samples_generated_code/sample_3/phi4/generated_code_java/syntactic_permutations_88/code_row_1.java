import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/calculate_price")
public class PriceCalculationServlet extends HttpServlet {

    private static final double PRODUCT_PRICES = {
        "product1": 10.0,
        "product2": 20.0,
        "product3": 30.0
    };

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String yamlPayload = req.getQueryString();
        
        Map<String, Object> parsedData = parseYaml(yamlPayload);
        String productCode = (String) parsedData.get("product_code");
        Integer quantity = (Integer) parsedData.get("quantity");

        double price = getProductPrice(productCode);
        if (price == -1.0) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid Product Code");
            return;
        }

        double totalPrice = price * quantity;
        resp.setContentType("text/plain");
        resp.getWriter().write(String.valueOf(totalPrice));
    }

    private Map<String, Object> parseYaml(String yamlPayload) {
        Yaml yaml = new Yaml();
        return yaml.load(yamlPayload);
    }

    private double getProductPrice(String productCode) {
        return PRODUCT_PRICES.getOrDefault(productCode, -1.0);
    }
}


To run this code:
- Ensure you have a Servlet container like Tomcat.
- Add dependencies for `snakeyaml` and `jackson-databind` in your project's build tool (e.g., Maven or Gradle). For Maven:


<dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>1.33</version>
</dependency>
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.15.0</version>
</dependency>