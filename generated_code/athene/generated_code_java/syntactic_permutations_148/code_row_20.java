import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class MessageServlet extends HttpServlet {
    private Connection dbConnection;

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        response.sendRedirect("main_page.jsp");
    }

    private void insert_user_message_in_db(String username, String message) {
        try (PreparedStatement pstmt = dbConnection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {
            pstmt.setString(1, username);
            pstmt.setString(2, message);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Message> messages = getMessagesFromDb();
        request.setAttribute("messages", messages);
        request.getRequestDispatcher("main_page.jsp").forward(request, response);
    }

    private List<Message> getMessagesFromDb() {
        List<Message> messages = new ArrayList<>();
        try (PreparedStatement pstmt = dbConnection.prepareStatement("SELECT * FROM messages")) {
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messages.add(new Message(username, message));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return messages;
    }

    private static class Message {
        private final String username;
        private final String message;

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