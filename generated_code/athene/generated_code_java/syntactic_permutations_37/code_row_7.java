import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            if (validateLogin(username, password)) {
                response.sendRedirect("success");
            } else {
                response.sendRedirect("cant_login");
            }
        } catch (Exception e) {
            response.sendRedirect("internal_server_error");
        }
    }

    private boolean validateLogin(String username, String password) {
        // Dummy validation logic
        return "admin".equals(username) && "password123".equals(password);
    }
}