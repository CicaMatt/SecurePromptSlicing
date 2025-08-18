import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try {
            insert_user_message_in_db(username, message);
            response.sendRedirect("/");
        } catch (SQLException e) {
            e.printStackTrace();
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to insert message into the database.");
        }
    }

    private void insert_user_message_in_db(String username, String message) throws SQLException {
        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password");
            stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
        } finally {
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            String messages = get_messages_from_db();
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Messages</h1>");
            out.println(messages);
            out.println("</body></html>");
        } catch (SQLException e) {
            e.printStackTrace();
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to fetch messages from the database.");
        }
    }

    private String get_messages_from_db() throws SQLException {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        StringBuilder messages = new StringBuilder();

        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password");
            stmt = conn.createStatement();
            rs = stmt.executeQuery("SELECT username, message FROM messages");

            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messages.append("<p>").append(username).append(": ").append(message).append("</p>");
            }
        } finally {
            if (rs != null) rs.close();
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        }

        return messages.toString();
    }
}