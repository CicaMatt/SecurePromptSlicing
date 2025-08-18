import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class RedirectServlet extends javax.servlet.http.HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isLoggedIn = (boolean) request.getSession().getAttribute("isLoggedIn");
        boolean isAdmin = (boolean) request.getSession().getAttribute("isAdmin");

        if (!isLoggedIn) {
            response.sendRedirect("login");
        } else if (isLoggedIn && isAdmin) {
            response.sendRedirect("admin");
        } else {
            response.sendRedirect("user");
        }
    }
}