import java.sql.*;
import javax.servlet.http.HttpServletRequest;

public class LoginController {
    public void doGet(HttpServletRequest request) {
        // Display login page
    }

    public void doPost(HttpServletRequest request) throws Exception {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        boolean authenticated = false;

        // Connect to database
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/login", "root", "");
        Statement stmt = con.createStatement();
        String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
        ResultSet rs = stmt.executeQuery(sql);
        if (rs.next()) {
            authenticated = true;
        }

        if (authenticated) {
            // Log user in and redirect to dashboard page
            request.getSession().setAttribute("username", username);
            response.sendRedirect("/dashboard");
        } else {
            // Redirect back to login page
            request.setAttribute("message", "Invalid credentials");
            request.getRequestDispatcher("/login").forward(request, response);
        }
    }
}