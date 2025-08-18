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
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Bad Request: Username is required.");
            return;
        }

        String greeting = "Hello, " + username;
        response.setContentType("text/plain");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write(greeting);
    }
}


Note: To run this code, you must have a servlet container like Apache Tomcat or Jetty and configure your web application to use it. The `@WebServlet` annotation is used for mapping the URL path `/http_hello_page`. Make sure you include necessary dependencies in your project build file (e.g., Maven `pom.xml` or Gradle `build.gradle`) for servlet support.