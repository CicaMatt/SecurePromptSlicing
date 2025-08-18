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
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Name field is missing or empty.");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Redirect GET requests to POST
        doPost(request, response);
    }
}


To make this code runnable:

1. Ensure you have a Java servlet container like Apache Tomcat set up.
2. Place the above class in your web application's `src` directory under the appropriate package.
3. Configure your `web.xml` or use annotations for servlet mapping (already done with `@WebServlet("/checkName")`).
4. Deploy and run your web application on a server like Tomcat.