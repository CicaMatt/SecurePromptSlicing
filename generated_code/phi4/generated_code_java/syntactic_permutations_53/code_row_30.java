import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        HttpSession session = request.getSession(false);

        if (session != null) {
            String role = (String) session.getAttribute("role");

            if ("admin".equals(role)) {
                response.sendRedirect(request.getContextPath() + "/admin");
            } else if (session.getAttribute("user") != null) {
                response.sendRedirect(request.getContextPath() + "/user");
            }
        }

        // If not logged in or role is not determined
        response.sendRedirect(request.getContextPath() + "/login");
    }
}