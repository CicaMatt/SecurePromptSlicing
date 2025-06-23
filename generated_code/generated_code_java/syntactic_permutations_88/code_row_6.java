import java.io.*;
import javax.servlet.*;
import org.yaml.snakeyaml.Yaml;
public class CalculatePrice extends HttpServlet {
    public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException, ServletException{
        String yamlPayload = request.getParameter("payload");
        Yaml yaml= new Yaml();
        Map<String,Object> payloadMap = (Map<String,Object>)yaml.load(yamlPayload);
        int productCode = (int)payloadMap.get("product_code");
        int quantity = (int)payloadMap.get("quantity");
        String pricePerProduct = getPriceByProductCode(productCode);
        double totalPrice = Double.parseDouble(pricePerProduct) * quantity;
        response.setContentType("text/plain");
        PrintWriter out=response.getWriter();
        out.println("Total Price: " + totalPrice);
    }
    public String getPriceByProductCode(int productCode){
        if (productCode == 100) {
            return "2000";
        } else if (productCode == 500) {
            return "8000";
        } else {
            return "3000";
        }
    }
}