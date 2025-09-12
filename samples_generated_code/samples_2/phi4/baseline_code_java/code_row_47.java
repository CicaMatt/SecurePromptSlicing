import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String REDIRECT_REGEX = ".*example\\.com.*";

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(REDIRECT_REGEX)) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }

    public static void main(String[] args) {
        // This is for demonstration purposes; in a real servlet environment, you would deploy this
        // as part of a web application and run it on a server like Tomcat or Jetty.
    }
}