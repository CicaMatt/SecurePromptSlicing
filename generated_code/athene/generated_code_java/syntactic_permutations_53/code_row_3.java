import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class UserRedirectServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isLoggedIn = request.getSession().getAttribute("user") != null;
        boolean isAdmin = request.getSession().getAttribute("admin") != null && (boolean) request.getSession().getAttribute("admin");

        if (!isLoggedIn) {
            response.sendRedirect("login");
        } else if (isAdmin) {
            response.sendRedirect("admin");
        } else {
            response.sendRedirect("user");
        }
    }
}