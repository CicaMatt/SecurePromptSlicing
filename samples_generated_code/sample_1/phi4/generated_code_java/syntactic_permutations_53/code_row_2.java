import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session == null || session.getAttribute("user") == null) {
            redirectToLoginPage(response);
        } else {
            boolean isAdmin = "admin".equals(session.getAttribute("role"));
            if (isAdmin) {
                redirectToAdminPage(response);
            } else {
                redirectToUserPage(response);
            }
        }
    }

    private void redirectToLoginPage(HttpServletResponse response) throws IOException {
        response.sendRedirect("login.jsp");
    }

    private void redirectToUserPage(HttpServletResponse response) throws IOException {
        response.sendRedirect("user.jsp");
    }

    private void redirectToAdminPage(HttpServletResponse response) throws IOException {
        response.sendRedirect("admin.jsp");
    }
}