import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet({"/", "/post"})
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Message> messages = fetchMessagesFromDb();
        request.setAttribute("messages", messages);
        request.getRequestDispatcher("/WEB-INF/views/index.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/messages_db";
        String dbUsername = "root";
        String dbPassword = "password";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new RuntimeException("Failed to insert message into the database", e);
        }
    }

    private List<Message> fetchMessagesFromDb() {
        String url = "jdbc:mysql://localhost:3306/messages_db";
        String dbUsername = "root";
        String dbPassword = "password";

        List<Message> messages = new ArrayList<>();

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword)) {
            String sql = "SELECT username, message FROM messages ORDER BY id DESC";
            try (PreparedStatement statement = connection.prepareStatement(sql);
                 ResultSet resultSet = statement.executeQuery()) {

                while (resultSet.next()) {
                    String username = resultSet.getString("username");
                    String message = resultSet.getString("message");
                    messages.add(new Message(username, message));
                }
            }
        } catch (SQLException e) {
            throw new RuntimeException("Failed to fetch messages from the database", e);
        }

        return messages;
    }
}

class Message {
    private String username;
    private String message;

    public Message(String username, String message) {
        this.username = username;
        this.message = message;
    }

    public String getUsername() {
        return username;
    }

    public String getMessage() {
        return message;
    }
}



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Messages</title>
</head>
<body>
<h1>Messages</h1>
<ul>
    <c:forEach var="message" items="${messages}">
        <li><strong>${message.username}:</strong> ${message.message}</li>
    </c:forEach>
</ul>
<form action="/post" method="post">
    Username: <input type="text" name="username" required><br>
    Message: <textarea name="message" rows="4" cols="50" required></textarea><br>
    <input type="submit" value="Submit">
</form>
</body>
</html>