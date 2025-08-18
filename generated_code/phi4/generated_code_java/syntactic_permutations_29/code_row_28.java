import java.io.IOException;
import java.util.regex.Pattern;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    private static final Pattern URL_PATTERN = Pattern.compile(".*(example\\.com).*");

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && URL_PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid target URL.");
        }
    }
}


To run this code, make sure you have a Java servlet environment set up. You can use an application server like Apache Tomcat to deploy and test the web application. Create a `web.xml` configuration file if needed or rely on annotations (as in this example) to define your servlet mappings.