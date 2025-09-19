import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches("^[\\w-]+\\.")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}


Note: This code assumes you have a servlet container like Apache Tomcat set up, and you are deploying this as part of a Java web application. Also, ensure your `web.xml` (or equivalent configuration) is configured to map the `/redirect` URL pattern to this servlet if not using annotations.