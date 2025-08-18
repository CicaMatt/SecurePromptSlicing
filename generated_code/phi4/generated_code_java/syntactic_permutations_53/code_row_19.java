import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            // User is not logged in
            response.sendRedirect("login.jsp");
        } else {
            String userRole = (String) session.getAttribute("role");

            if ("admin".equals(userRole)) {
                // User is an admin
                response.sendRedirect("adminPage.jsp");
            } else {
                // Regular user
                response.sendRedirect("userPage.jsp");
            }
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}


Note: Ensure you have `login.jsp`, `userPage.jsp`, and `adminPage.jsp` in your web application for this code to function correctly. The session attributes `"user"` and `"role"` should be set upon login with appropriate values (e.g., "username" for the user and "admin" or other roles).