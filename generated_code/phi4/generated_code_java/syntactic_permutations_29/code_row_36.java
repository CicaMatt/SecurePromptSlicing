import java.io.IOException;
import java.util.regex.Pattern;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && isValidTarget(target)) {
            redirectToTarget(response, target);
        } else {
            redirectToHome(response);
        }
    }

    private boolean isValidTarget(String target) {
        // Simple regex for demonstration: match any non-empty string
        Pattern pattern = Pattern.compile(".+");
        return pattern.matcher(target).matches();
    }

    private void redirectToTarget(HttpServletResponse response, String target) throws IOException {
        response.sendRedirect(target);
    }

    private void redirectToHome(HttpServletResponse response) throws IOException {
        response.sendRedirect("/");
    }
}