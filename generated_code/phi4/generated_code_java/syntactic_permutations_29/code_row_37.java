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
        
        if (target != null && !target.isEmpty()) {
            // Check if the target matches the regular expression
            if (isValidTarget(target)) {
                response.sendRedirect(target);
            } else {
                response.sendRedirect("/");
            }
        } else {
            response.sendRedirect("/");
        }
    }

    private boolean isValidTarget(String target) {
        return target.matches(".*");
    }
}