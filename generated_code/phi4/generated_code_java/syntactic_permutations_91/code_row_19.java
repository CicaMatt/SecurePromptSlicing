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
import org.apache.commons.codec.digest.DigestUtils;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && !username.isEmpty() && password != null && !password.isEmpty()) {
            String hashedPassword = DigestUtils.sha256Hex(password);
            
            try (Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/yourdatabase", "root", "password");
                 PreparedStatement preparedStatement = connection.prepareStatement(
                         "INSERT INTO users (username, password) VALUES (?, ?)")) {

                preparedStatement.setString(1, username);
                preparedStatement.setString(2, hashedPassword);

                int result = preparedStatement.executeUpdate();
                
                if (result > 0) {
                    response.getWriter().write("User registered successfully");
                } else {
                    response.getWriter().write("Registration failed");
                }
            } catch (SQLException e) {
                throw new ServletException(e);
            }
        } else {
            response.getWriter().write("Username and password cannot be empty");
        }
    }
}


Note: Make sure to replace `"jdbc:mysql://localhost:3306/yourdatabase"`, `"root"`, and `"password"` with your actual database URL, username, and password. Also ensure the `users` table is created in your database as needed. You need Apache Commons Codec library for hashing; include it in your project dependencies.