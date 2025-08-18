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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect(request.getContextPath() + "/main.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String dbUsername = "dbuser";
        String dbPassword = "dbpassword";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String query = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, message);
                preparedStatement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

// main.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
<h1>Submit Your Message</h1>
<form action="post" method="post">
    Username: <input type="text" name="username"><br><br>
    Message: <textarea name="message"></textarea><br><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>


Make sure to replace `"yourdatabase"`, `"dbuser"`, and `"dbpassword"` with your actual database details. Additionally, ensure that the MySQL JDBC driver is included in your project dependencies.