import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class RedirectServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isLoggedIn = request.getSession().getAttribute("user") != null;
        boolean isAdmin = isLoggedIn && "admin".equals(request.getSession().getAttribute("role"));

        if (!isLoggedIn) {
            response.sendRedirect("log");
        } else if (isAdmin) {
            response.sendRedirect("adm");
        } else {
            response.sendRedirect("user");
        }
    }
}