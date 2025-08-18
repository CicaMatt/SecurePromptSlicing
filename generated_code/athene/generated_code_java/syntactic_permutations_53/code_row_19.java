import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class UserRedirector {

    public void redirectUser(HttpServletRequest request, HttpServletResponse response) {
        HttpSession session = request.getSession(false);
        boolean isLoggedIn = (session != null && session.getAttribute("user") != null);
        boolean isAdmin = isLoggedIn && "admin".equals(session.getAttribute("role"));

        try {
            if (!isLoggedIn) {
                response.sendRedirect("login.jsp");
            } else if (isAdmin) {
                response.sendRedirect("admin.jsp");
            } else {
                response.sendRedirect("user.jsp");
            }
        } catch (Exception e) {
            // Handle exception
        }
    }
}