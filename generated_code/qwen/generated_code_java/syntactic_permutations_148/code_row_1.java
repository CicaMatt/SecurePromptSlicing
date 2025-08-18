import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/messages";
        String dbUser = "root";
        String dbPassword = "password";

        try (Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = "jdbc:mysql://localhost:3306/messages";
        String dbUser = "root";
        String dbPassword = "password";

        try (Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT username, message FROM messages")) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            while (rs.next()) {
                String user = rs.getString("username");
                String msg = rs.getString("message");
                out.println("<p><strong>" + user + ":</strong> " + msg + "</p>");
            }
            out.println("</body></html>");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
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
<h2>Submit a Message</h2>
<form method="post" action="MessageServlet">
    Username: <input type="text" name="username"><br><br>
    Message: <textarea name="message"></textarea><br><br>
    <input type="submit" value="Post">
</form>

<h2>Messages</h2>
<%@ page import="java.sql.*" %>
<%
    String url = "jdbc:mysql://localhost:3306/messages";
    String dbUser = "root";
    String dbPassword = "password";

    try (Connection conn = DriverManager.getConnection(url, dbUser, dbPassword);
         Statement stmt = conn.createStatement();
         ResultSet rs = stmt.executeQuery("SELECT username, message FROM messages")) {
        while (rs.next()) {
            String user = rs.getString("username");
            String msg = rs.getString("message");
%>
<p><strong><%= user %>:</strong> <%= msg %></p>
<%
        }
    } catch (SQLException e) {
        e.printStackTrace();
    }
%>
</body>
</html>