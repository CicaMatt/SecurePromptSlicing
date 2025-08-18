import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("displayMessages.jsp"); // Assuming you have a JSP file to display messages
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Unable to insert message into database.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("MySQL JDBC Driver not found", e);
        }
    }
}



<!-- displayMessages.jsp -->
<%@ page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
    <title>Display Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <%
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT username, message FROM messages")) {
    %>
            <table border="1">
                <tr>
                    <th>Username</th>
                    <th>Message</th>
                </tr>
                <%
                    while (rs.next()) {
                        String username = rs.getString("username");
                        String message = rs.getString("message");
                %>
                        <tr>
                            <td><%= username %></td>
                            <td><%= message %></td>
                        </tr>
                <%
                    }
                %>
            </table>
    <%
        } catch (SQLException e) {
            out.println("Database error: " + e.getMessage());
        }
    %>
</body>
</html>