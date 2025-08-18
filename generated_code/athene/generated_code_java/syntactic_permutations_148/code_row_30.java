import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class MessageServlet extends HttpServlet {
    private Connection conn;

    public void init() throws ServletException {
        // Initialize database connection
        // Example: conn = Database.getConnection();
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect(request.getContextPath() + "/");
    }

    private void insert_user_message_in_db(String username, String message) {
        try (PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fetch messages from the database
        try (PreparedStatement stmt = conn.prepareStatement("SELECT * FROM messages")) {
            ResultSet rs = stmt.executeQuery();
            StringBuilder messagesHtml = new StringBuilder("<ul>");
            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messagesHtml.append("<li>").append(username).append(": ").append(message).append("</li>");
            }
            messagesHtml.append("</ul>");
            request.setAttribute("messages", messagesHtml.toString());
        } catch (SQLException e) {
            e.printStackTrace();
        }

        // Forward to the JSP page to display messages
        request.getRequestDispatcher("/index.jsp").forward(request, response);
    }
}