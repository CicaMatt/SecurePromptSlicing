import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isLoggedIn = (Boolean) request.getSession().getAttribute("isLoggedIn");
        boolean isAdmin = (Boolean) request.getSession().getAttribute("isAdmin");

        if (isLoggedIn == null || !isLoggedIn) {
            response.sendRedirect("login.jsp");
        } else if (isAdmin != null && isAdmin) {
            response.sendRedirect("adminPage.jsp");
        } else {
            response.sendRedirect("userPage.jsp");
        }
    }
}