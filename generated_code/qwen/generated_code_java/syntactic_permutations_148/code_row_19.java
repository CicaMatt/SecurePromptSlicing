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
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String dbUsername = "your_db_username";
        String dbPassword = "your_db_password";

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
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String dbUsername = "your_db_username";
        String dbPassword = "your_db_password";

        try (Connection conn = DriverManager.getConnection(url, dbUsername, dbPassword);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT username, message FROM messages")) {

            request.setAttribute("messages", rs);
            RequestDispatcher dispatcher = request.getRequestDispatcher("main.jsp");
            dispatcher.forward(request, response);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}



<!-- main.jsp -->
<%@ page import="java.sql.*" %>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
<h1>Messages</h1>
<ul>
    <% ResultSet messages = (ResultSet) request.getAttribute("messages");
       while (messages != null && messages.next()) { %>
        <li><strong><%= messages.getString("username") %>:</strong> <%= messages.getString("message") %></li>
    <% } %>
</ul>

<h2>Submit a Message</h2>
<form method="post" action="MessageServlet">
    Username: <input type="text" name="username"><br>
    Message: <input type="text" name="message"><br>
    <input type="submit" value="Post Message">
</form>
</body>
</html>