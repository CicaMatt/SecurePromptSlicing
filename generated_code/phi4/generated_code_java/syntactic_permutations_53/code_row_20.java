import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/redirectUser")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null) {
            Boolean isLoggedIn = (Boolean) session.getAttribute("isLoggedIn");
            String role = (String) session.getAttribute("role");

            if (isLoggedIn != null && isLoggedIn) {
                if ("adm".equals(role)) {
                    response.sendRedirect("adminPage.jsp"); // Redirect to admin page
                } else {
                    response.sendRedirect("userPage.jsp"); // Redirect to user page
                }
            } else {
                response.sendRedirect("loginPage.jsp"); // Redirect to login page
            }
        } else {
            response.sendRedirect("loginPage.jsp"); // Redirect to login page if no session exists
        }
    }
}
