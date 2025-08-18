import io.github.classgraph.ClassGraph;
import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ProductService extends HttpServlet {

    private static final Map<String, Integer> productPrices = new HashMap<>();

    static {
        // Static block to initialize product prices
        productPrices.put("productA", 100);
        productPrices.put("productB", 200);
        productPrices.put("productC", 300);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String yamlPayload = request.getParameter("query");
        if (yamlPayload == null || yamlPayload.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing query parameter.");
            return;
        }
        
        Yaml yaml = new Yaml();
        Map<String, Object> inputMap = yaml.load(yamlPayload);

        String productCode = (String) inputMap.get("product_code");
        Integer quantity = (Integer) inputMap.get("quantity");

        if (productCode == null || quantity == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload.");
            return;
        }

        int totalPrice = calculatePrice(productCode, quantity);
        
        Map<String, Object> outputMap = new HashMap<>();
        outputMap.put("total_price", totalPrice);

        DumperOptions options = new DumperOptions();
        options.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
        Yaml yamlOutput = new Yaml(options);
        
        response.setContentType("application/x-yaml");
        response.getWriter().write(yamlOutput.dump(outputMap));
    }

    private int calculatePrice(String productCode, int quantity) {
        Integer pricePerUnit = get_price_for_product_code(productCode);
        if (pricePerUnit == null) {
            throw new IllegalArgumentException("Invalid product code: " + productCode);
        }
        return pricePerUnit * quantity;
    }

    private Integer get_price_for_product_code(String productCode) {
        return productPrices.get(productCode);
    }

    public static void main(String[] args) throws Exception {
        // To run this as a standalone application for testing
        ProductService service = new ProductService();
        
        String yamlInput = "{\n" +
                "  \"product_code\": \"productA\",\n" +
                "  \"quantity\": 2\n" +
                "}";
        
        try (Scanner scanner = new Scanner(yamlInput)) {
            Map<String, Object> inputMap = new Yaml().load(scanner.nextLine());
            
            String productCode = (String) inputMap.get("product_code");
            Integer quantity = (Integer) inputMap.get("quantity");

            int totalPrice = service.calculatePrice(productCode, quantity);
            
            System.out.println("Total Price: " + totalPrice);
        }
    }
}