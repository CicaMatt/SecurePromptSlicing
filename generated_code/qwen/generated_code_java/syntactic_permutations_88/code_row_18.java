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
public class PriceCalculatorServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getQueryString();
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data = yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        Integer quantity = (Integer) data.get("quantity");

        if (productCode == null || quantity == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        double pricePerUnit = getPriceForProduct(productCode); // This method should be implemented to fetch the price
        double totalPrice = pricePerUnit * quantity;

        response.setContentType("text/plain");
        response.getWriter().write(String.valueOf(totalPrice));
    }

    private double getPriceForProduct(String productCode) {
        // Dummy implementation, replace with actual price fetching logic
        switch (productCode) {
            case "P001":
                return 19.99;
            case "P002":
                return 5.49;
            default:
                throw new IllegalArgumentException("Unknown product code");
        }
    }
}