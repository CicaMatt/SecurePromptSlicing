import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/http_hello_page")
public class HelloServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        handleRequest(request, response);
    }

    private void handleRequest(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String username = req.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }
        
        res.setContentType("text/plain");
        PrintWriter out = res.getWriter();
        out.println("Hello " + username);
    }
}


To run this code, you will need to have a servlet container such as Apache Tomcat. Save the above Java class in your `src` directory under a package (e.g., `com.example`). Adjust your project structure and build path accordingly if using an IDE like IntelliJ or Eclipse.

In addition, ensure that your `web.xml` is configured properly to map the servlet URL pattern `/http_hello_page`, or rely on the `@WebServlet("/http_hello_page")` annotation as shown above. Deploy the application to a server such as Tomcat and access it through the appropriate URL (e.g., `http://localhost:8080/yourAppContext/http_hello_page?username=YourName`).