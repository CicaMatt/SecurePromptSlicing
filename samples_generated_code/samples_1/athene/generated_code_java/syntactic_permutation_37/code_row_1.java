import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final String CORRECT_USERNAME = "admin";
    private static final String CORRECT_PASSWORD = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            String username = request.getParameter("username");
            String password = request.getParameter("password");

            if (CORRECT_USERNAME.equals(username) && CORRECT_PASSWORD.equals(password)) {
                response.sendRedirect("success");
            } else {
                response.sendRedirect("cant_login");
            }
        } catch (Exception e) {
            response.sendRedirect("internal_server_error");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}