import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (username != null && message != null) {
            insertUserMessageInDb(username, message);
            response.sendRedirect("main.jsp"); // Redirect to main page
        }
    }

    private void insertUserMessageInDb(String username, String message) {
        // Placeholder for database insertion logic
        // Implement the actual database interaction here
    }
}

// JSP file (main.jsp)
<%@ page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
    <title>Main Page</title>
</head>
<body>

<h2>Messages</h2>
<%
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;

    try {
        Class.forName("com.mysql.cj.jdbc.Driver");
        conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "username", "password");

        stmt = conn.createStatement();
        String sql = "SELECT username, message FROM messages ORDER BY created_at DESC";
        rs = stmt.executeQuery(sql);

        while (rs.next()) {
            String user = rs.getString("username");
            String msg = rs.getString("message");
            out.println("<p><strong>" + user + "</strong>: " + msg + "</p>");
        }
    } catch (Exception e) {
        e.printStackTrace();
    } finally {
        try { if (rs != null) rs.close(); } catch (SQLException ex) { ex.printStackTrace(); }
        try { if (stmt != null) stmt.close(); } catch (SQLException ex) { ex.printStackTrace(); }
        try { if (conn != null) conn.close(); } catch (SQLException ex) { ex.printStackTrace(); }
    }
%>

<form action="post" method="post">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username"><br><br>
    <label for="message">Message:</label>
    <textarea id="message" name="message"></textarea><br><br>
    <button type="submit">Post</button>
</form>

</body>
</html>