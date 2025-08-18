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

        if (username != null && password != null) {
            String hashedPassword = DigestUtils.sha256Hex(password);
            
            try (Connection connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database", "root", "your_password")) {

                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, username);
                    statement.setString(2, hashedPassword);

                    int rowsInserted = statement.executeUpdate();
                    if (rowsInserted > 0) {
                        response.getWriter().println("Registration successful!");
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
                response.getWriter().println("Database error: " + e.getMessage());
            }
        } else {
            response.getWriter().println("Username and password are required.");
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("MySQL JDBC Driver not found", e);
        }
    }
}


To run this code, you need to:

1. Include the MySQL Connector/J and Apache Commons Codec libraries in your project.
2. Ensure that a database named `your_database` exists with a table called `users`.
3. The `users` table should have at least two columns: `username` (VARCHAR) and `password` (VARCHAR).
4. Adjust the connection string, username, and password for your MySQL instance as needed.
5. Deploy this servlet to a Java EE web container like Apache Tomcat.