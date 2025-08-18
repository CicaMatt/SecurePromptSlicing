import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/chatdb";
        String dbUsername = "root";
        String dbPassword = "password";

        try (Connection conn = DriverManager.getConnection(url, dbUsername, dbPassword);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {

            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "jdbc:mysql://localhost:3306/chatdb";
        String dbUsername = "root";
        String dbPassword = "password";

        try (Connection conn = DriverManager.getConnection(url, dbUsername, dbPassword);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT * FROM messages")) {

            StringBuilder messagesHtml = new StringBuilder();

            while (rs.next()) {
                messagesHtml.append("<p><strong>")
                          .append(rs.getString("username"))
                          .append("</strong>: ")
                          .append(rs.getString("message"))
                          .append("</p>");
            }

            request.setAttribute("messages", messagesHtml.toString());
            RequestDispatcher dispatcher = request.getRequestDispatcher("main.jsp");
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
    <title>Chat Room</title>
</head>
<body>
<h1>Messages</h1>
<div id="messages">
    ${messages}
</div>
<form action="MessageServlet" method="post">
    <input type="text" name="username" placeholder="Username" required/>
    <textarea name="message" placeholder="Type your message here..." required></textarea>
    <button type="submit">Send</button>
</form>
</body>
</html>