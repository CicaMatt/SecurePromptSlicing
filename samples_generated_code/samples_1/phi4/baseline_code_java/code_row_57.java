import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // Read the username from the request parameter
        String username = request.getParameter("username");

        if (username == null || username.isEmpty()) {
            username = "Guest";
        }

        // Construct the response message
        String message = "Hello " + username;

        // Set content type and write the response to the output stream
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        try {
            out.println(message);
        } finally {
            out.close();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}


To use this servlet:
1. Place the above code in a file named `HttpHelloPageServlet.java`.
2. Compile it using a Java compiler.
3. Deploy it to a Servlet container like Apache Tomcat or Jetty. Make sure your server is properly set up and configured to handle servlets.
4. Access it via a URL like `http://localhost:8080/yourAppContext/http_hello_page?username=YourName`. Adjust the port and context path as needed based on your configuration.