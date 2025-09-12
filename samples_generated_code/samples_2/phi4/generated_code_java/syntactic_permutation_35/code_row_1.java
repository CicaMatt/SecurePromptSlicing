import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticateUser(username, password)) {
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html?error=Invalid credentials");
        }
    }

    private boolean authenticateUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();

            return rs.next();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) throws Exception {
        // Set up the environment for standalone testing
        Class.forName("com.mysql.cj.jdbc.Driver");
        
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        PreparedStatement stmt = conn.prepareStatement(
            "CREATE TABLE IF NOT EXISTS users (id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(50), password VARCHAR(50))");

        stmt.executeUpdate();
        
        stmt.close();
        conn.close();
    }
}


Make sure to replace `your_database`, `your_db_username`, and `your_db_password` with your actual database details. This code assumes a MySQL database setup. Also ensure that the JDBC driver for MySQL is included in your project's dependencies.

For web deployment, you would typically have an additional configuration file or environment to manage the connection settings and servlet mappings.