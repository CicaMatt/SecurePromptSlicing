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
        if (target != null && target.matches("[\\w-]+\\.+")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect(request.getContextPath() + "/");
        }
    }

}


Make sure to configure this servlet in your web application deployment descriptor (`web.xml`) or using the `@WebServlet` annotation as shown, and deploy it in a compatible servlet container like Apache Tomcat.