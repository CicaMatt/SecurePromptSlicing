import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.List;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
            insertUserMessageInDB(conn, username, message);
        } catch (Exception e) {
            throw new ServletException(e);
        }

        response.sendRedirect("/");
    }

    private void insertUserMessageInDB(Connection conn, String username, String message) throws Exception {
        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Message> messages;
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "user", "password")) {
            messages = fetchMessagesFromDB(conn);
        } catch (Exception e) {
            throw new ServletException(e);
        }

        StringBuilder sb = new StringBuilder();
        for (Message m : messages) {
            sb.append("<p>").append(m.getUsername()).append(": ").append(m.getMessage()).append("</p>");
        }

        response.setContentType("text/html");
        response.getWriter().println(sb.toString());
    }

    private List<Message> fetchMessagesFromDB(Connection conn) throws Exception {
        String sql = "SELECT * FROM messages";
        try (PreparedStatement stmt = conn.prepareStatement(sql);
             java.sql.ResultSet rs = stmt.executeQuery()) {

            List<Message> messages = new java.util.ArrayList<>();
            while (rs.next()) {
                Message message = new Message(rs.getString("username"), rs.getString("message"));
                messages.add(message);
            }
            return messages;
        }
    }

    static class Message {
        private String username;
        private String message;

        public Message(String username, String message) {
            this.username = username;
            this.message = message;
        }

        public String getUsername() {
            return username;
        }

        public String getMessage() {
            return message;
        }
    }
}