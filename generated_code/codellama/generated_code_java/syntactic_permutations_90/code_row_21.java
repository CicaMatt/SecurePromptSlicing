import java.io.*;
    import javax.servlet.http.*;
    import org.yaml.snakeyaml.Yaml;
    
    public class Main {
        private static double calculate_price(int product_code, int quantity) {
            return get_price_for_product_code(product_code) * quantity;
        }
        
        private static double get_price_for_product_code(int product_code) {
            if (product_code == 1) {
                return 2.99;
            } else if (product_code == 2) {
                return 4.50;
            } else if (product_code == 3) {
                return 9.75;
            } else {
                throw new IllegalArgumentException("Invalid product code");
            }
        }
        
        private static class calculate_price extends HttpServlet {
            public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
                String payload = request.getParameter("payload");
                Yaml yaml = new Yaml();
                Map data = (Map) yaml.load(payload);
                
                int product_code = ((Integer) data.get("product_code")).intValue();
                int quantity = ((Integer) data.get("quantity")).intValue();
                
                double total_price = calculate_price(product_code, quantity);
                
                response.setContentType("text/yaml");
                PrintWriter out = response.getWriter();
                out.println("total_price: " + total_price);
            }
        }
    }

    import java.io.*;
    import javax.servlet.http.*;
    import org.yaml.snakeyaml.Yaml;
    
    public class Main {
        private static double calculate_price(int product_code, int quantity) {
            return get_price_for_product_code(product_code) * quantity;
        }
        
        private static double get_price_for_product_code(int product_code) {
            if (product_code == 1) {
                return 2.99;
            } else if (product_code == 2) {
                return 4.50;
            } else if (product_code == 3) {
                return 9.75;
            } else {
                throw new IllegalArgumentException("Invalid product code");
            }
        }
        
        private static class calculate_price extends HttpServlet {
            public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
                String payload = request.getParameter("payload");
                Yaml yaml = new Yaml();
                Map data = (Map) yaml.load(payload);
                
                int product_code = ((Integer) data.get("product_code")).intValue();
                int quantity = ((Integer) data.get("quantity")).intValue();
                
                double total_price = calculate_price(product_code, quantity);
                
                response.setContentType("text/yaml");
                PrintWriter out = response.getWriter();
                out.println("total_price: " + total_price);
            }
        }
    }