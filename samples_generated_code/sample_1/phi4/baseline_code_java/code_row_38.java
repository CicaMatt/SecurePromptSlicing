import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    private static final String TARGET_REGEX = ".*example\\.com.*";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(TARGET_REGEX)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}


To run this code:

1. Set up a Java web application environment with a servlet container like Apache Tomcat.
2. Place the above `RedirectServlet` class in your project's source directory.
3. Configure the `web.xml` or use annotations to map the servlet as shown.
4. Deploy the application on your server and access it via `/redirect?target=<URL>`.