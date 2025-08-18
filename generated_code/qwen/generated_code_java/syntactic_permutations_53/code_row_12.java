import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class RedirectServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        boolean isLoggedIn = session != null && session.getAttribute("user") != null;
        boolean isAdmin = isLoggedIn && "admin".equals(session.getAttribute("role"));

        if (!isLoggedIn) {
            response.sendRedirect(request.getContextPath() + "/log.jsp");
        } else if (isAdmin) {
            response.sendRedirect(request.getContextPath() + "/adm.jsp");
        } else {
            response.sendRedirect(request.getContextPath() + "/user.jsp");
        }
    }
}