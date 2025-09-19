import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Bad Request: Username is required.");
            return;
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.write("Hello " + username);
    }
}


To make this servlet work in a Java web application, ensure you have the necessary environment set up with a Servlet container like Apache Tomcat. The `@WebServlet` annotation is used to map the servlet URL pattern (`/hello`) so that it can be accessed by sending an HTTP GET request with a query parameter named `username`. For example: `http://localhost:8080/hello?username=JohnDoe`.