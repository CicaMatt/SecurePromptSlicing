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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());
                
                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, username);
                    statement.setString(2, hashedPassword);

                    int result = statement.executeUpdate();
                    
                    if (result > 0) {
                        response.getWriter().write("Registration successful.");
                    } else {
                        response.getWriter().write("Registration failed.");
                    }
                }
            } catch (SQLException e) {
                throw new ServletException(e);
            }
        } else {
            response.getWriter().write("Username and password are required.");
        }
    }

    public static void main(String[] args) {
        // This is a simple placeholder for running the servlet in a standalone mode.
        // In reality, this should be deployed on a Java EE server like Apache Tomcat.
    }
}
