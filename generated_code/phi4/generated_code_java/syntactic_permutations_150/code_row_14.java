import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("mainPage.jsp");  // Redirect to the main page
    }

    private void insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/yourDatabase"; 
        String user = "root";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();  // Handle exceptions appropriately
        }
    }
}



<!-- mainPage.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Submit Your Message</h1>
    <form action="post" method="POST">
        Username: <input type="text" name="username" required><br>
        Message: <textarea name="message" required></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>