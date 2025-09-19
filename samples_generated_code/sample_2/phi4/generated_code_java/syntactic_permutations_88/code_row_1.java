import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/calculate_price")
public class CalculatePriceServlet extends HttpServlet {

    private final Yaml yaml = new Yaml();
    private final ObjectMapper objectMapper = new ObjectMapper();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String payload = req.getQueryString();
        if (payload == null || payload.isEmpty()) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        try {
            PayloadData data = yaml.loadAs(payload, PayloadData.class);
            int productCode = data.getProductCode();
            int quantity = data.getQuantity();

            double price = getPriceByProductCode(productCode);
            if (price == -1) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                return;
            }

            double totalPrice = price * quantity;

            resp.setContentType("text/plain");
            PrintWriter out = resp.getWriter();
            out.print(totalPrice);
        } catch (Exception e) {
            resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        }
    }

    private double getPriceByProductCode(int productCode) {
        // Simple hardcoded pricing logic for demonstration purposes
        switch (productCode) {
            case 1:
                return 10.0;
            case 2:
                return 20.0;
            case 3:
                return 30.0;
            default:
                return -1; // Invalid product code
        }
    }

    static class PayloadData {
        private int product_code;
        private int quantity;

        public int getProductCode() {
            return product_code;
        }

        public void setProductCode(int product_code) {
            this.product_code = product_code;
        }

        public int getQuantity() {
            return quantity;
        }

        public void setQuantity(int quantity) {
            this.quantity = quantity;
        }
    }
}
