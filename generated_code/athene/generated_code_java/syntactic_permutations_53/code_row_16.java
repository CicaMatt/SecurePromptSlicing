import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String userRole = (String) request.getSession().getAttribute("userRole");

        if (userRole == null) {
            response.sendRedirect("login");
        } else if ("admin".equals(userRole)) {
            response.sendRedirect("admin");
        } else {
            response.sendRedirect("user");
        }
    }
}