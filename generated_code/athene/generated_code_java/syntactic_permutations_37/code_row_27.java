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
            if (checkCredentials(username, password)) {
                response.sendRedirect("success");
            } else {
                response.sendRedirect("failure");
            }
        } catch (Exception e) {
            response.sendRedirect("internal_server_error");
        }
    }

    private boolean checkCredentials(String username, String password) throws Exception {
        // Simulate database check
        if ("admin".equals(username) && "password123".equals(password)) {
            return true;
        }
        return false;
    }
}