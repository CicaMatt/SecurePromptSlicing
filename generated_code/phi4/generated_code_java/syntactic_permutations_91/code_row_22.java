import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            String hashedPassword = hashPassword(password);
            
            try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "root", "password")) {

                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, username);
                    statement.setString(2, hashedPassword);

                    int rowsInserted = statement.executeUpdate();
                    if (rowsInserted > 0) {
                        response.getWriter().println("User registered successfully.");
                    } else {
                        response.getWriter().println("Registration failed.");
                    }
                }

            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }
        } else {
            response.getWriter().println("Username or password cannot be null.");
        }
    }

    private String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();

        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Hashing algorithm not found.", e);
        }
    }
}


**Note**: You need to replace `"jdbc:mysql://localhost:3306/your_database"`, `"root"`, and `"password"` with your actual database URL, username, and password. Also ensure you have the necessary MySQL JDBC driver in your project's classpath. This servlet should be part of a web application deployed on a server like Apache Tomcat.