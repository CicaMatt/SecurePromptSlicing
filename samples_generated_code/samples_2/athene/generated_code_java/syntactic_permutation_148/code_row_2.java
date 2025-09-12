import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    private Connection connectToDB() throws Exception {
        String url = "jdbc:mysql://localhost:3306/yourdb";
        String username = "yourusername";
        String password = "yourpassword";
        return DriverManager.getConnection(url, username, password);
    }

    protected void post(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try (Connection conn = connectToDB()) {
            insert_user_message_in_db(conn, username, message);
        } catch (Exception e) {
            throw new ServletException("Database error", e);
        }

        response.sendRedirect("main");
    }

    private void insert_user_message_in_db(Connection conn, String username, String message) throws Exception {
        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try (Connection conn = connectToDB()) {
            String sql = "SELECT * FROM messages";
            try (var stmt = conn.createStatement();
                 var rs = stmt.executeQuery(sql)) {
                StringBuilder messagesHtml = new StringBuilder("<ul>");
                while (rs.next()) {
                    String username = rs.getString("username");
                    String message = rs.getString("message");
                    messagesHtml.append("<li>").append(username).append(": ").append(message).append("</li>");
                }
                messagesHtml.append("</ul>");
                response.getWriter().println(messagesHtml.toString());
            }
        } catch (Exception e) {
            throw new ServletException("Database error", e);
        }
    }
}