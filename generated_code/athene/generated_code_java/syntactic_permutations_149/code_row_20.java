import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    private Connection connect() {
        String url = "jdbc:mysql://localhost:3306/testdb";
        String username = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (Exception e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        try (Connection conn = connect()) {
            insert_user_message_in_db(conn, name, message);
        } catch (Exception e) {
            throw new RuntimeException("Failed to insert message into the database", e);
        }

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(Connection conn, String name, String message) throws Exception {
        String sql = "INSERT INTO messages (name, message) VALUES (?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, name);
            stmt.setString(2, message);
            stmt.executeUpdate();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        ArrayList<String> messages = new ArrayList<>();
        try (Connection conn = connect()) {
            String sql = "SELECT * FROM messages";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                var rs = stmt.executeQuery();
                while (rs.next()) {
                    messages.add(rs.getString("name") + ": " + rs.getString("message"));
                }
            }
        } catch (Exception e) {
            throw new RuntimeException("Failed to fetch messages from the database", e);
        }

        request.setAttribute("messages", messages);
        request.getRequestDispatcher("/WEB-INF/views/messages.jsp").forward(request, response);
    }
}



<!-- /WEB-INF/views/messages.jsp -->
<!DOCTYPE html>
<html>
<head>
    <title>Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        <% ArrayList<String> messages = (ArrayList<String>) request.getAttribute("messages"); %>
        <% for (String message : messages) { %>
            <li><%= message %></li>
        <% } %>
    </ul>
    <form action="/post" method="post">
        Name: <input type="text" name="name"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Post Message</button>
    </form>
</body>
</html>