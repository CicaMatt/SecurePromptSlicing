import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {
    private static final String USER_SESSION_KEY = "user";
    private static final String ADMIN_ROLE_KEY = "isAdmin";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && session.getAttribute(USER_SESSION_KEY) != null) {
            Boolean isAdmin = (Boolean) session.getAttribute(ADMIN_ROLE_KEY);
            
            if (isAdmin != null && isAdmin) {
                redirectToPage(response, "adm");
            } else {
                redirectToPage(response, "user");
            }
        } else {
            redirectToPage(response, "log");
        }
    }

    private void redirectToPage(HttpServletResponse response, String page) throws IOException {
        response.sendRedirect(page + ".jsp");
    }
}