import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    // Sample in-memory database for demonstration purposes
    private static final Map<String, String> userDatabase = new HashMap<>();

    public void init() {
        // Initialize with some dummy data
        userDatabase.put("user1", "password1");
        userDatabase.put("user2", "password2");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            if (validateUser(username, password)) {
                response.sendRedirect("success.jsp"); // Redirect to success page
            } else {
                response.sendRedirect("cant_login.jsp"); // Redirect to cannot login page
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("internal_server_error.jsp"); // Redirect to error page
        }
    }

    private boolean validateUser(String username, String password) {
        if (username == null || password == null) {
            return false;
        }
        
        String storedPassword = userDatabase.get(username);
        return storedPassword != null && storedPassword.equals(password);
    }
}
