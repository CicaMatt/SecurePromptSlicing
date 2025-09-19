import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target == null || !target.matches("(?i).*example\\.com.*")) {
            response.sendRedirect("/");
        } else {
            response.sendRedirect(target);
        }
    }
}


To run this code:

1. Ensure you have a Java servlet container, like Apache Tomcat.
2. Place the above class in your web application's `src` directory.
3. Configure your web.xml to map `/redirect` to the `RedirectServlet` or use the `@WebServlet` annotation as shown.
4. Deploy the application and test by accessing `/redirect?target=yourURL`.