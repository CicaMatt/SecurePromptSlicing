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

@WebServlet("/addMessage")
public class MessageServlet extends HttpServlet {
    private Connection getConnection() throws Exception {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String username = "root";
        String password = "password";
        return DriverManager.getConnection(url, username, password);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try (Connection conn = getConnection()) {
            insert_user_message_in_db(conn, username, message);
        } catch (Exception e) {
            e.printStackTrace();
        }

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(Connection conn, String username, String message) throws Exception {
        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, message);
            pstmt.executeUpdate();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Message> messages;
        try (Connection conn = getConnection()) {
            messages = getMessagesFromDB(conn);
        } catch (Exception e) {
            throw new ServletException("Could not retrieve messages", e);
        }

        request.setAttribute("messages", messages);
        request.getRequestDispatcher("/WEB-INF/views/messages.jsp").forward(request, response);
    }

    private List<Message> getMessagesFromDB(Connection conn) throws Exception {
        String sql = "SELECT * FROM messages";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            return fetchMessages(pstmt);
        }
    }

    private List<Message> fetchMessages(PreparedStatement pstmt) throws Exception {
        List<Message> messages = new java.util.ArrayList<>();
        try (var rs = pstmt.executeQuery()) {
            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messages.add(new Message(username, message));
            }
        }
        return messages;
    }

    public class Message {
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