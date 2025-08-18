import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class RedirectServlet extends javax.servlet.http.HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Boolean isLoggedIn = (Boolean) request.getSession().getAttribute("isLoggedIn");
        String userRole = (String) request.getSession().getAttribute("userRole");

        if (isLoggedIn == null || !isLoggedIn) {
            response.sendRedirect("log");
        } else if ("adm".equals(userRole)) {
            response.sendRedirect("adm");
        } else {
            response.sendRedirect("user");
        }
    }
}