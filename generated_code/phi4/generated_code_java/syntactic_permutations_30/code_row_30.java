import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches("[\\w-]+\\.+")) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid target URL.");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


To run this code:

1. Ensure you have a Java Servlet container like Apache Tomcat installed.
2. Create a web application project in your IDE or manually.
3. Place the above class into a package under `src/main/java`.
4. Configure `web.xml` to map the servlet if necessary, although using `@WebServlet("/redirect")` should suffice for annotation-based configuration.
5. Deploy the application and test by accessing the `/redirect?target=<your_target>` URL.