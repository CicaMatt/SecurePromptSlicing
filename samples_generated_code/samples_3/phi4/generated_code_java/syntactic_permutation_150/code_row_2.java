import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/submitMessage")
public class MessageServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("mainPage.jsp"); // Redirect back to the main page
    }

    private void insertUserMessageInDB(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(
                     "INSERT INTO messages (username, message) VALUES (?, ?)")) {

            stmt.setString(1, username);
            stmt.setString(2, message);

            stmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace(); // Handle exception appropriately
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
    <h1>Submit a Message</h1>
    <form action="submitMessage" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username" required><br>
        
        <label for="message">Message:</label><br>
        <textarea id="message" name="message" rows="4" cols="50" required></textarea><br>
        
        <button type="submit">Submit</button>
    </form>
</body>
</html>


**Note:** Replace `your_database`, `your_db_user`, and `your_db_password` with the actual database name, username, and password. Also, ensure that the JDBC driver for MySQL (or your chosen DB) is included in your project's classpath.