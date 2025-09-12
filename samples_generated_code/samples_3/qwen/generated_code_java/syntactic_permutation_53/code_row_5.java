import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String userRole = (String) request.getSession().getAttribute("userRole");
        
        if (userRole == null) {
            response.sendRedirect("login.jsp");
        } else if ("admin".equalsIgnoreCase(userRole)) {
            response.sendRedirect("admin.jsp");
        } else {
            response.sendRedirect("user.jsp");
        }
    }
}