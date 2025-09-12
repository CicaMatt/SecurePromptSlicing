import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/RedirectServlet")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.html"); // Redirect to login page if not logged in
        } else {
            String role = (String) session.getAttribute("role");
            
            if ("admin".equalsIgnoreCase(role)) {
                response.sendRedirect("adminPage.jsp"); // Redirect to admin page if user is an admin
            } else {
                response.sendRedirect("userPage.jsp"); // Redirect to user page if logged in but not an admin
            }
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}