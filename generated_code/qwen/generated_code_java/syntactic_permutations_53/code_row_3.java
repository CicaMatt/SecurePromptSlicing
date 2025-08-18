import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class LoginRedirectServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isLoggedIn = (boolean) request.getSession().getAttribute("isLoggedIn");
        boolean isAdmin = (boolean) request.getSession().getAttribute("isAdmin");

        if (!isLoggedIn) {
            response.sendRedirect("/login.jsp");
        } else if (isAdmin) {
            response.sendRedirect("/admin.jsp");
        } else {
            response.sendRedirect("/user.jsp");
        }
    }
}