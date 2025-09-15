import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("index.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/messages_db";
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
        String url = "jdbc:mysql://localhost:3306/messages_db";
        String dbUsername = "root";
        String dbPassword = "password";

        try (Connection conn = DriverManager.getConnection(url, dbUsername, dbPassword);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT username, message FROM messages ORDER BY id DESC")) {

            response.setContentType("text/html");
            PrintWriter out = response.getWriter();

            out.println("<html><body>");
            out.println("<h1>Messages</h1>");
            out.println("<form method='post' action='/MessageServlet'>");
            out.println("<input type='text' name='username' placeholder='Username' required><br>");
            out.println("<textarea name='message' placeholder='Message' required></textarea><br>");
            out.println("<button type='submit'>Post</button>");
            out.println("</form>");
            out.println("<hr>");

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
}
