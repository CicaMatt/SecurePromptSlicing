import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session == null || session.getAttribute("user") == null) {
            // User is not logged in
            response.sendRedirect(request.getContextPath() + "/login.jsp");
        } else {
            String userRole = (String) session.getAttribute("role");

            if ("admin".equalsIgnoreCase(userRole)) {
                // User is an admin
                response.sendRedirect(request.getContextPath() + "/admin.jsp");
            } else {
                // User is logged in but not an admin
                response.sendRedirect(request.getContextPath() + "/user.jsp");
            }
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
