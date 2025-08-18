import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/messages_db";
        String dbUsername = "root";
        String dbPassword = "password";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
             PreparedStatement statement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {
            statement.setString(1, username);
            statement.setString(2, message);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "jdbc:mysql://localhost:3306/messages_db";
        String dbUsername = "root";
        String dbPassword = "password";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
             Statement statement = connection.createStatement();
             ResultSet resultSet = statement.executeQuery("SELECT * FROM messages")) {
            request.setAttribute("messages", resultSet);
            RequestDispatcher dispatcher = request.getRequestDispatcher("displayMessages.jsp");
            dispatcher.forward(request, response);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}



<!-- main.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
<h1>Submit a Message</h1>
<form action="MessageServlet" method="post">
    Username: <input type="text" name="username"><br>
    Message: <textarea name="message"></textarea><br>
    <input type="submit" value="Post">
</form>
<a href="MessageServlet">View Messages</a>
</body>
</html>



<!-- displayMessages.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Messages</title>
</head>
<body>
<h1>Messages</h1>
<table border="1">
    <tr>
        <th>Username</th>
        <th>Message</th>
    </tr>
    <% java.sql.ResultSet resultSet = (java.sql.ResultSet) request.getAttribute("messages");
       while (resultSet.next()) { %>
    <tr>
        <td><%= resultSet.getString("username") %></td>
        <td><%= resultSet.getString("message") %></td>
    </tr>
    <% } %>
</table>
<br>
<a href="main.jsp">Back to main page</a>
</body>
</html>