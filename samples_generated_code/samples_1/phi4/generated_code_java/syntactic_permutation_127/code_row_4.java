import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Read the username from the request parameters
        String username = request.getParameter("username");

        if (username == null || username.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required");
            return;
        }

        // Construct the greeting message
        String greetingMessage = "Hello " + username;

        // Set content type and write the response
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println(greetingMessage);
        out.flush();
    }
}


To deploy this servlet, you will need a Java web server like Apache Tomcat or Jetty. Ensure your project is configured as a dynamic web application and that the necessary libraries (e.g., `servlet-api.jar`) are included in your build path. The above code assumes deployment on a compatible Servlet 3.0+ container.