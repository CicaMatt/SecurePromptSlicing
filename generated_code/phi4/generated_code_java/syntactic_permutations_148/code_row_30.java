import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("mainPage.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        // Assume a simple JDBC setup for demonstration purposes
        try (java.sql.Connection connection = java.sql.DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourDatabase", "username", "password")) {

            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (java.sql.PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, message);

                statement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

// Main Page JSP to display messages
/*
<%@ page import="java.sql.*" %>
<html>
<head><title>Main Page</title></head>
<body>
<h1>Messages</h1>
<table border="1">
    <tr>
        <th>Username</th>
        <th>Message</th>
    </tr>
    <% 
        try (Connection connection = DriverManager.getConnection(
            "jdbc:mysql://localhost:3306/yourDatabase", "username", "password")) {

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT username, message FROM messages");

            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String message = resultSet.getString("message");
    %>
    <tr>
        <td><%= username %></td>
        <td><%= message %></td>
    </tr>
    <% 
            }
        } catch (SQLException e) {
            out.println("Error retrieving messages: " + e.getMessage());
        }
    %>
</table>
</body>
</html>
*/