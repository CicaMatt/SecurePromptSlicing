import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class CheckNameServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        
        if (name != null && !name.isEmpty()) {
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Field 'name' is missing or empty.");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}


To make this code runnable in a web application environment like Apache Tomcat:

1. Create a new dynamic web project in your IDE (e.g., Eclipse, IntelliJ).
2. Add the above servlet class to `src/main/java` folder.
3. Ensure you have a `web.xml` configuration file or use annotations as shown for servlet mapping.
4. Deploy the application to a suitable Java EE server like Apache Tomcat.