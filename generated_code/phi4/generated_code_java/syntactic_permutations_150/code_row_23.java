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

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Assuming main page is mainPage.jsp
        } else {
            response.sendRedirect("errorPage.jsp"); // Redirect to an error page if insertion fails
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase";
        String dbUsername = "root"; // Update with your database username
        String dbPassword = "password"; // Update with your database password

        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";

        try (
            Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)
        ) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);

            int affectedRows = preparedStatement.executeUpdate();
            return affectedRows > 0;
        } catch (SQLException e) {
            e.printStackTrace(); // Handle the exception appropriately
            return false;
        }
    }
}
