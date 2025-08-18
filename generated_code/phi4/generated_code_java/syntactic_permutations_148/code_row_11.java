import java.io.IOException;
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

        insert_user_message_in_db(username, message);

        response.sendRedirect("mainPage.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
        // Example using JDBC (pseudo-code):
        /*
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/database_name", "username", "password")) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        */
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fetch messages from database and set as attribute
        try {
            List<Message> messages = fetchMessagesFromDb();
            request.setAttribute("messages", messages);
            request.getRequestDispatcher("/displayMessages.jsp").forward(request, response);
        } catch (SQLException e) {
            throw new ServletException("Error fetching messages", e);
        }
    }

    private List<Message> fetchMessagesFromDb() throws SQLException {
        // Database retrieval logic here
        // Example using JDBC (pseudo-code):
        /*
        List<Message> messages = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/database_name", "username", "password")) {
            String sql = "SELECT username, message FROM messages";
            try (Statement statement = connection.createStatement();
                 ResultSet resultSet = statement.executeQuery(sql)) {
                while (resultSet.next()) {
                    String username = resultSet.getString("username");
                    String message = resultSet.getString("message");
                    messages.add(new Message(username, message));
                }
            }
        }
        return messages;
        */
        return new ArrayList<>(); // Return an empty list for now
    }

    private static class Message {
        private final String username;
        private final String message;

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
}



<!-- displayMessages.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Display Messages</title>
</head>
<body>
<h2>Messages:</h2>
<ul>
    <% List<PostServlet.Message> messages = (List<PostServlet.Message>) request.getAttribute("messages");
       for (PostServlet.Message msg : messages) { %>
        <li><strong><%= msg.getUsername() %>:</strong> <%= msg.getMessage() %></li>
    <% } %>
</ul>
</body>
</html>