import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        out.println("<html>");
        out.println("<body>");
        out.println("<form action='LoginServlet' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            // Simple check for admin
            if ("admin".equals(username) && "adminpass".equals(password)) {
                response.sendRedirect("admin_page.jsp");
            } else {
                response.sendRedirect("login.jsp");
            }
        } else {
            response.sendRedirect("login.jsp");
        }
    }

    public static void main(String[] args) {
        // Main method to launch a simple server (for demonstration purposes)
        // This is not part of the standard servlet implementation
        try {
            HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
            HttpContext context = server.createContext("/LoginServlet", new LoginHandler());
            server.setExecutor(null); // creates a default executor
            server.start();
            System.out.println("Server started on port 8080");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static class LoginHandler implements HttpHandler {
        public void handle(HttpExchange exchange) throws IOException {
            String requestMethod = exchange.getRequestMethod();

            if ("GET".equals(requestMethod)) {
                ServletInputStream inputStream = exchange.getRequestBody();
                // Simulate doGet
                PrintWriter out = new PrintWriter(exchange.getResponseBody());
                
                out.println("<html>");
                out.println("<body>");
                out.println("<form action='LoginServlet' method='POST'>");
                out.println("Username: <input type='text' name='username'><br>");
                out.println("Password: <input type='password' name='password'><br>");
                out.println("<input type='submit' value='Login'>");
                out.println("</form>");
                out.println("</body>");
                out.println("</html>");

                exchange.sendResponseHeaders(200, out.size());
                out.close();
            } else if ("POST".equals(requestMethod)) {
                // Simulate doPost
                InputStreamReader isr = new InputStreamReader(exchange.getRequestBody(), "utf-8");
                BufferedReader br = new BufferedReader(isr);
                
                String username = "";
                String password = "";
                String line;
                while ((line = br.readLine()) != null) {
                    if (line.startsWith("username=")) {
                        username = line.substring(9);
                    } else if (line.startsWith("password=")) {
                        password = line.substring(9);
                    }
                }

                if ("admin".equals(username) && "adminpass".equals(password)) {
                    exchange.getResponseHeaders().add("Location", "http://localhost:8080/admin_page.jsp");
                    exchange.sendResponseHeaders(302, -1); // Redirect
                } else {
                    exchange.getResponseHeaders().add("Location", "http://localhost:8080/login.jsp");
                    exchange.sendResponseHeaders(302, -1); // Redirect to login page
                }
            }
        }
    }
}