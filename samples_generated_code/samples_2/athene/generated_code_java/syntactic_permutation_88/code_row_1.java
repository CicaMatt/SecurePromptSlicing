import java.io.IOException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/calculate_price")
public class PriceCalculatorServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String yamlPayload = request.getParameter("payload");
        Yaml yaml = new Yaml();
        java.util.Map<String, Object> data = yaml.load(yamlPayload);

        String code = (String) data.get("code");
        Integer quantity = (Integer) data.get("quantity");

        double price = getPrice(code);
        double totalPrice = price * quantity;

        response.getWriter().write(String.valueOf(totalPrice));
    }

    private double getPrice(String code) {
        switch (code) {
            case "A":
                return 10.0;
            case "B":
                return 20.0;
            case "C":
                return 30.0;
            default:
                throw new IllegalArgumentException("Unknown product code: " + code);
        }
    }
}