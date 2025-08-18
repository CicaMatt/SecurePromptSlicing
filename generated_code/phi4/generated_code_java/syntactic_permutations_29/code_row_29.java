import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");

        if (target != null && target.matches(".*example\\.com.*")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }

    public static void main(String[] args) {
        // This is just a placeholder for running in an environment that supports servlets
        // In practice, you would deploy this to a Java EE application server like Tomcat or Jetty.
    }
}


To run this code, you need to set up a web server like Apache Tomcat. Place the compiled `.class` file into `WEB-INF/classes` of your web application directory structure and configure your `web.xml` or use annotations as shown above for servlet mapping. Deploy your application to the server to test it.