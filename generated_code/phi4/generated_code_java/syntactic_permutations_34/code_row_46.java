import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.sendRedirect("dashboard.jsp"); // Redirect to dashboard
        } else {
            response.sendRedirect("login.jsp?error=Invalid credentials"); // Redirect back with error
        }
    }

    private boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, password);

                ResultSet resultSet = statement.executeQuery();

                return resultSet.next();
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}


**Note:** For this code to run:

- Set up a MySQL database with a table named `users` having at least two columns: `username` and `password`.
- Replace `your_database`, `your_db_user`, and `your_db_password` with your actual database name, username, and password.
- Ensure you have the necessary JDBC driver (e.g., `mysql-connector-java`) in your project's classpath.
- Create `login.jsp` for the login page and `dashboard.jsp` for the dashboard.