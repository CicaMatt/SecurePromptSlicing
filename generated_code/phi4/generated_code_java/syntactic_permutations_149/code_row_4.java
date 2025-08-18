import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/message")
public class MessageServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect("/");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {

            stmt.setString(1, username);
            stmt.setString(2, message);

            int affectedRows = stmt.executeUpdate();
            return affectedRows > 0;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = fetchMessagesFromDb();

        request.setAttribute("messages", messages);
        request.getRequestDispatcher("/display.jsp").forward(request, response);
    }

    private List<String> fetchMessagesFromDb() {
        List<String> messages = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT username, message FROM messages");
             java.sql.ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messages.add(username + ": " + message);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return messages;
    }
}



<!-- display.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        <% List<String> messages = (List<String>) request.getAttribute("messages");
           if (messages != null) {
               for (String msg : messages) { %>
                   <li><%= msg %></li>
            <%  }
           } else { %>
               <li>No messages to display.</li>
        <%  } %>
    </ul>
</body>
</html>


Make sure to replace `yourdatabase`, `root`, and `password` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project's classpath.