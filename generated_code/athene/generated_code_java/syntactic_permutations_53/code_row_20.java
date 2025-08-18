import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class UserRedirectServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isLoggedIn = (boolean) request.getSession().getAttribute("isLoggedIn");
        boolean isAdmin = (boolean) request.getSession().getAttribute("isAdmin");

        if (!isLoggedIn) {
            response.sendRedirect("log");
        } else if (isLoggedIn && isAdmin) {
            response.sendRedirect("adm");
        } else {
            response.sendRedirect("user");
        }
    }
}