import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class AuthenticationServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        boolean isLoggedIn = (session != null && session.getAttribute("user") != null);
        boolean isAdmin = isLoggedIn && Boolean.TRUE.equals(session.getAttribute("isAdmin"));

        if (!isLoggedIn) {
            response.sendRedirect("login.jsp");
        } else if (isAdmin) {
            response.sendRedirect("adminPage.jsp");
        } else {
            response.sendRedirect("userPage.jsp");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}