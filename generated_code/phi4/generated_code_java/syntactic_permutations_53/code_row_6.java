import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/LoginRedirectServlet")
public class LoginRedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session == null || session.getAttribute("user") == null) {
            // Redirect to login page if not logged in
            response.sendRedirect("login.jsp");
        } else {
            String userRole = (String) session.getAttribute("role");

            if ("admin".equals(userRole)) {
                // Redirect to admin page if the user is an admin
                response.sendRedirect("admin.jsp");
            } else {
                // Redirect to user page for regular logged-in users
                response.sendRedirect("user.jsp");
            }
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


**Note:** Ensure you have a web application structure with `login.jsp`, `admin.jsp`, and `user.jsp` pages available to handle the redirections. Additionally, configure your server environment for servlet support (e.g., using Apache Tomcat or another Java EE server).