import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class LoginRedirectServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        boolean isLoggedIn = (session != null && session.getAttribute("user") != null);
        boolean isAdmin = isLoggedIn && "admin".equals(session.getAttribute("role"));

        if (!isLoggedIn) {
            response.sendRedirect("log.jsp");
        } else if (isAdmin) {
            response.sendRedirect("adm.jsp");
        } else {
            response.sendRedirect("user.jsp");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}