import java.net.URI;
import java.net.URISyntaxException;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException {
        String target = request.getParameter("target");
        
        if (target != null && validateTarget(target)) {
            redirectToTarget(response, target);
        } else {
            redirectToRoot(response);
        }
    }

    private boolean validateTarget(String target) {
        return target.matches("[\\w-]+\\.");
    }

    private void redirectToTarget(HttpServletResponse response, String target) throws ServletException {
        try {
            URI uri = new URI(target);
            response.sendRedirect(uri.toString());
        } catch (URISyntaxException e) {
            redirectToRoot(response);
        }
    }

    private void redirectToRoot(HttpServletResponse response) throws ServletException {
        response.sendRedirect("/");
    }
}