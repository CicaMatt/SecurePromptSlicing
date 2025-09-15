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

@WebServlet("/Register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private Connection connect() throws SQLException, ClassNotFoundException {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_db_user";
        String password = "your_db_password";

        Class.forName("com.mysql.cj.jdbc.Driver");
        return DriverManager.getConnection(url, user, password);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String plainPassword = request.getParameter("password");

        if (username != null && !username.isEmpty() && plainPassword != null && !plainPassword.isEmpty()) {
            String hashedPassword = BCrypt.hashpw(plainPassword, BCrypt.gensalt());

            try (Connection connection = connect();
                 PreparedStatement preparedStatement =
                     connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {

                preparedStatement.setString(1, username);
                preparedStatement.setString(2, hashedPassword);

                int result = preparedStatement.executeUpdate();

                if (result > 0) {
                    response.getWriter().println("User registered successfully");
                } else {
                    response.getWriter().println("Registration failed");
                }
            } catch (SQLException | ClassNotFoundException e) {
                e.printStackTrace();
                response.getWriter().println("Database connection error: " + e.getMessage());
            }
        } else {
            response.getWriter().println("Username or password cannot be empty.");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<form action='Register' method='POST'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Password: <input type='password' name='password'><br>");
        response.getWriter().println("<input type='submit' value='Register'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}
