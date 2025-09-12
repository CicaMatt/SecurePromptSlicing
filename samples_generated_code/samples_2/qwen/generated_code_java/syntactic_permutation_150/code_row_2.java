import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insertUserMessageInDb(username, message);
        }

        response.sendRedirect("index.html");
    }

    private void insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/messages_db";
        String dbUser = "root";
        String dbPassword = "password";

        try (Connection conn = DriverManager.getConnection(url, dbUser, dbPassword)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                stmt.setString(2, message);
                stmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}

// index.html
// This file should be placed in the web application's root directory
/*
<!DOCTYPE html>
<html>
<head>
    <title>Message Board</title>
</head>
<body>
    <h1>Submit a Message</h1>
    <form action="post" method="post">
        Username: <input type="text" name="username"><br><br>
        Message: <textarea name="message"></textarea><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>
*/