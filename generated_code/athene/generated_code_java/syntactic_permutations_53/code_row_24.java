import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class UserRedirector {

    public void redirectToAppropriatePage(HttpServletRequest request, HttpServletResponse response) {
        HttpSession session = request.getSession(false);
        boolean isLoggedIn = (session != null && session.getAttribute("user") != null);
        boolean isAdmin = isLoggedIn && "admin".equals(session.getAttribute("role"));

        try {
            if (!isLoggedIn) {
                response.sendRedirect("login");
            } else if (isAdmin) {
                response.sendRedirect("admin");
            } else {
                response.sendRedirect("user");
            }
        } catch (Exception e) {
            // Handle exception
        }
    }
}