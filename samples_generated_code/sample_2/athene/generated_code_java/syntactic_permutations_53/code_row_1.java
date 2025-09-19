import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class UserRedirectServlet extends javax.servlet.http.HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String userRole = (String) request.getSession().getAttribute("userRole");
        
        if (userRole == null) {
            response.sendRedirect("login.jsp");
        } else if ("user".equals(userRole)) {
            response.sendRedirect("user.jsp");
        } else if ("admin".equals(userRole)) {
            response.sendRedirect("admin.jsp");
        }
    }
}