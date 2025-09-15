import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.mindrot.jbcrypt.BCrypt;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null && !username.isEmpty() && !password.isEmpty()) {
            try {
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

                Connection conn = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/webapp", "root", "password");

                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                PreparedStatement statement = conn.prepareStatement(sql);
                statement.setString(1, username);
                statement.setString(2, hashedPassword);

                int result = statement.executeUpdate();
                if (result > 0) {
                    response.getWriter().println("User registered successfully.");
                } else {
                    response.getWriter().println("Registration failed.");
                }

                statement.close();
                conn.close();
            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }
        } else {
            response.getWriter().println("Username and password cannot be empty.");
        }
    }
}
