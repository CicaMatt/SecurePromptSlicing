import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.HashMap;
import java.util.Map;

public class Main extends HttpServlet {
    
    private static final long serialVersionUID = 1L;

    //define price for each product code
    static Map<String, Integer> productsPrice = new HashMap<String, Integer>();
    static{
        productsPrice.put("A1", 25);
        productsPrice.put("B2", 20);
        productsPrice.put("C3", 15);
    }
    
    //define function that returns the price for a product code
    public static int calculatePrice(String productCode, int quantity){
        if (productsPrice.containsKey(productCode)){
            return productsPrice.get(productCode) * quantity;
        } else {
            throw new RuntimeException("Product Code not recognized");
        }
    }
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        
        //define route that calculates the price for a product code and quantity.
        String productCode = request.getParameter("productCode");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        response.setContentType("text/plain");
        response.getWriter().println(calculatePrice(productCode, quantity));
    }
    
    public static void main(String[] args) throws Exception {
        
        //define a web app. defines a function that returns the price for a product code
        HttpServer server = HttpServer.create(new InetSocketAddress(5000), 0);
        server.createContext("/", new Main());
        server.setExecutor(null);
        server.start();
    }
}