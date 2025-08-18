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

        if (username != null && password != null && !username.isEmpty() && !password.isEmpty()) {
            String hashedPassword = DigestUtils.sha256Hex(password);

            try (Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database", "root", "your_password");
                 PreparedStatement preparedStatement = connection.prepareStatement(
                         "INSERT INTO users (username, password) VALUES (?, ?)")) {

                preparedStatement.setString(1, username);
                preparedStatement.setString(2, hashedPassword);

                int result = preparedStatement.executeUpdate();
                if (result > 0) {
                    response.getWriter().println("User registered successfully!");
                } else {
                    response.getWriter().println("Registration failed.");
                }
            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }
        } else {
            response.getWriter().println("Username and password are required.");
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("JDBC Driver not found", e);
        }
    }
}


Make sure to replace `"jdbc:mysql://localhost:3306/your_database"`, `"root"`, and `"your_password"` with your actual database URL, username, and password. Also, ensure that the MySQL JDBC driver is in your classpath (e.g., by including it in your `pom.xml` if you're using Maven).