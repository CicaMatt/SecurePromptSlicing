import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isLoggedIn = (boolean) request.getSession().getAttribute("isLoggedIn");
        boolean isAdmin = (boolean) request.getSession().getAttribute("isAdmin");

        if (!isLoggedIn) {
            response.sendRedirect("login.jsp");
        } else if (isAdmin) {
            response.sendRedirect("admin.jsp");
        } else {
            response.sendRedirect("user.jsp");
        }
    }
}