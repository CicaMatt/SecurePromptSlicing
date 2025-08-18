import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final String REGEX_PATTERN = "your-regex-pattern-here";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String targetQueryParameter = request.getParameter("target");

        if (targetQueryParameter != null && targetQueryParameter.matches(REGEX_PATTERN)) {
            response.sendRedirect(targetQueryParameter);
        } else {
            response.sendRedirect(request.getContextPath() + "/");
        }
    }

    public static void main(String[] args) throws Exception {
        // This is a placeholder for running in an embedded server, like Jetty or Tomcat.
        // For standalone testing, configure the web.xml and deploy to a servlet container.
        System.out.println("Deploy this servlet to a Java EE compatible server.");
    }
}