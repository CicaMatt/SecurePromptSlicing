import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {

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
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Bad Request: Username is required");
            return;
        }
        
        String greetingMessage = "Hello, " + username;
        response.setContentType("text/plain");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write(greetingMessage);
    }
}


To run this code:
1. Ensure you have a Java servlet container like Apache Tomcat or Jetty.
2. Place the above class in your `src` directory under an appropriate package if needed.
3. Configure your web application's `web.xml` to map the servlet URL pattern `/http_hello_page`.
4. Deploy and run your web application, then access it via `http://localhost:8080/yourAppName/http_hello_page?username=YourName`.