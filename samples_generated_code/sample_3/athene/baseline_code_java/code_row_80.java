import java.util.Map;
import java.util.HashMap;
import org.yaml.snakeyaml.Yaml;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    private Map<String, Double> productPrices = new HashMap<>();

    public PriceCalculatorServlet() {
        // Initialize with some product codes and prices
        productPrices.put("A123", 10.5);
        productPrices.put("B456", 20.0);
        productPrices.put("C789", 5.75);
    }

    private double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, 0.0);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> data = (Map<String, Object>) yaml.load(yamlPayload);

        String productCode = (String) data.get("product_code");
        int quantity = ((Number) data.get("quantity")).intValue();

        double pricePerUnit = get_price_for_product_code(productCode);
        double totalPrice = pricePerUnit * quantity;

        Map<String, Double> result = new HashMap<>();
        result.put("total_price", totalPrice);

        response.setContentType("application/x-yaml");
        PrintWriter out = response.getWriter();
        out.print(yaml.dump(result));
    }
}