import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkModerator")
public class ModeratorCheckServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String username = request.getParameter("username");
        
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "your_username", "your_password")) {

            String query = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                
                ResultSet resultSet = statement.executeQuery();
                
                if (resultSet.next()) {
                    boolean isModerator = resultSet.getBoolean("is_moderator");
                    response.getWriter().write(String.valueOf(isModerator));
                } else {
                    response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                    response.getWriter().write("User not found.");
                }
            }
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for the server setup, typically handled by a servlet container like Tomcat or Jetty.
    }
}


Ensure you have the necessary JDBC driver in your classpath and configure your database connection details accordingly. The code assumes using MySQL as the database. Adjust the JDBC URL, username, password, and database schema as needed for your specific setup.