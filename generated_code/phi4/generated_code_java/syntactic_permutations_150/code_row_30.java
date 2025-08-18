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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect("main.jsp?status=success");
        } else {
            response.sendRedirect("main.jsp?status=failure");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Submit Your Message</h1>

    <form action="post" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br><br>
        
        <label for="message">Message:</label><br>
        <textarea id="message" name="message"></textarea><br><br>

        <button type="submit">Submit</button>
    </form>

    <script>
        if (new URLSearchParams(window.location.search).get('status') === 'success') {
            alert("Your message has been posted successfully!");
        } else if (new URLSearchParams(window.location.search).get('status') === 'failure') {
            alert("Failed to post your message. Please try again.");
        }
    </script>
</body>
</html>