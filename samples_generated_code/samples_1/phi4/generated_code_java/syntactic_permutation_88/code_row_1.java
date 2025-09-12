import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/calculate_price")
public class CalculatePriceServlet extends HttpServlet {

    private static final int PRICE_PER_UNIT = 100; // Example price per unit

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String queryParam = request.getQueryString();
        if (queryParam != null) {
            Yaml yaml = new Yaml();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()))) {
                Object yamlObject = yaml.load(reader);
                if (yamlObject instanceof java.util.Map<?, ?>) {
                    java.util.Map<String, Object> map = (java.util.Map<String, Object>) yamlObject;
                    String productCode = (String) map.get("product_code");
                    Integer quantity = (Integer) map.get("quantity");

                    if (productCode != null && quantity != null) {
                        int totalPrice = PRICE_PER_UNIT * quantity;
                        response.setContentType("text/plain");
                        response.getWriter().write(String.valueOf(totalPrice));
                    } else {
                        response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid product_code or quantity.");
                    }
                } else {
                    response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid YAML format.");
                }
            } catch (Exception e) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while processing the request.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No query parameter provided.");
        }
    }
}