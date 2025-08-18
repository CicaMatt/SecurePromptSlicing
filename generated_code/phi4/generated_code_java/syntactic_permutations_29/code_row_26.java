import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    private static final String REDIRECT_REGEX = ".*example\\.com.*";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(REDIRECT_REGEX)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}


To run this code:

1. You need to have a servlet container like Apache Tomcat.
2. Create a web.xml or use the `@WebServlet` annotation for deployment configuration.
3. Deploy the application in the servlet container.