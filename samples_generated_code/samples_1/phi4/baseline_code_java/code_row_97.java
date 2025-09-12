import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.yaml.snakeyaml.Yaml;

@WebServlet("/calculate_price")
public class CalculatePriceServlet extends HttpServlet {
    
    private static final String PRICE_LIST = "price_list.yml";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        // Fetch the YAML payload from the query parameter
        String yamlPayload = request.getQueryString();
        Yaml yaml = new Yaml();
        Object obj = yaml.load(yamlPayload);
        if (obj instanceof Map<String, Object> && ((Map<?, ?>) obj).containsKey("product_code") && 
            ((Map<?, ?>) obj).containsKey("quantity")) {
            
            String productCode = (String) ((Map<?, ?>) obj).get("product_code");
            int quantity = Integer.parseInt((String) ((Map<?, ?>) obj).get("quantity"));
        
            // Load the price list from a YAML file
            Yaml yamlPriceList = new Yaml();
            Map<String, Double> priceList;
            try (InputStream in = getClass().getClassLoader().getResourceAsStream(PRICE_LIST)) {
                if (in == null) {
                    response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Price list not found.");
                    return;
                }
                priceList = yamlPriceList.load(in);
            }
            
            // Calculate the total price
            Double productPrice = priceList.get(productCode);
            if (productPrice != null) {
                double totalPrice = productPrice * quantity;
                response.setContentType("text/plain");
                response.getWriter().write(String.valueOf(totalPrice));
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid product code.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload format.");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doGet(request, response);
    }
}