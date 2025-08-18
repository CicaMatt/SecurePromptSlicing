import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HttpHelloPageServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Set response content type
        response.setContentType("text/plain");
        
        // Get the username from the request parameters
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            response.getWriter().write("Hello Guest");
        } else {
            response.getWriter().write("Hello " + username);
        }
    }

    public static void main(String[] args) {
        // This class is typically run in a servlet container like Apache Tomcat or Jetty
    }
}


**Note**: 
- This code assumes you are running it within a servlet container (like Apache Tomcat).
- The `@WebServlet("/hello")` annotation maps the servlet to the URL `/hello`.
- To test this, deploy the servlet in a web application server and access `http://localhost:8080/yourAppName/hello?username=YourName`.