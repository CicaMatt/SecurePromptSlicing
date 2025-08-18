import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            username = "World";
        }
        
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println("hello " + username);
    }

    public static void main(String[] args) {
        // Main method is required for standalone execution.
        // In a real environment, this servlet would be deployed on a server like Apache Tomcat or Jetty.
    }
}