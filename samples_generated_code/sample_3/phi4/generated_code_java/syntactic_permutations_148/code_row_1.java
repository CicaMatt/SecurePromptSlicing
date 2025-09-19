import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect("main.jsp");
    }

    private void insert_user_message_in_db(String name, String message) {
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourdatabase", "username", "password")) {

            String query = "INSERT INTO messages (name, message) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, name);
                preparedStatement.setString(2, message);

                preparedStatement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws ServletException, IOException {
        // This is a placeholder for running the servlet in standalone mode
        // Typically, you would deploy this to a server like Tomcat or Jetty.
    }
}

// Main.jsp (simplified example of displaying messages)
/*
<%@ page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Messages</h1>
    <form action="post" method="POST">
        Name: <input type="text" name="name"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>

    <%
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/yourdatabase", "username", "password")) {

            String query = "SELECT * FROM messages";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query);
                 ResultSet resultSet = preparedStatement.executeQuery()) {

                while (resultSet.next()) {
                    String name = resultSet.getString("name");
                    String message = resultSet.getString("message");

                    out.println("<p><strong>" + name + "</strong>: " + message + "</p>");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    %>
</body>
</html>
*/

// Ensure you have the MySQL JDBC driver in your classpath.