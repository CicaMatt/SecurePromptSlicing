import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String REGEX_PATTERN = ".*example\\.com.*";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(REGEX_PATTERN)) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid target URL.");
        }
    }

    public static void main(String[] args) {
        // This is just a placeholder to satisfy the requirement for a runnable code.
        System.out.println("Please deploy this servlet in a Java EE compatible server like Tomcat or Jetty.");
    }
}