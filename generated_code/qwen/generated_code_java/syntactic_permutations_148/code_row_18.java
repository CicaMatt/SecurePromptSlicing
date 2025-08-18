import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insertUserMessageInDB(message);
        response.sendRedirect("/");
    }

    private void insertUserMessageInDB(String message) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO messages (content) VALUES (?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, message);
                stmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @WebServlet("/")
    public static class MainServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            List<String> messages = getMessagesFromDB();
            request.setAttribute("messages", messages);
            request.getRequestDispatcher("/WEB-INF/views/main.jsp").forward(request, response);
        }

        private List<String> getMessagesFromDB() {
            String url = "jdbc:mysql://localhost:3306/your_database";
            String user = "root";
            String password = "password";
            List<String> messages = new ArrayList<>();

            try (Connection conn = DriverManager.getConnection(url, user, password)) {
                String sql = "SELECT content FROM messages ORDER BY id DESC";
                try (PreparedStatement stmt = conn.prepareStatement(sql);
                     ResultSet rs = stmt.executeQuery()) {
                    while (rs.next()) {
                        messages.add(rs.getString("content"));
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            return messages;
        }
    }
}



<!-- WEB-INF/views/main.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
<h1>Messages</h1>
<ul>
    <% for (String message : (List<String>) request.getAttribute("messages")) { %>
        <li><%= message %></li>
    <% } %>
</ul>
<form action="/post" method="post">
    <input type="text" name="message" placeholder="Enter your message here"/>
    <button type="submit">Send</button>
</form>
</body>
</html>