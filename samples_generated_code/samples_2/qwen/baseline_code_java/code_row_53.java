import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Message> messages = getMessagesFromDB();
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        for (Message message : messages) {
            out.println("<p>" + message.getUsername() + ": " + message.getMessage() + "</p>");
        }
        out.println("<form action=\"/post\" method=\"post\">");
        out.println("Username: <input type=\"text\" name=\"username\"><br>");
        out.println("Message: <textarea name=\"message\"></textarea><br>");
        out.println("<input type=\"submit\" value=\"Post Message\">");
        out.println("</form>");
        out.println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/testdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, message);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private List<Message> getMessagesFromDB() {
        String url = "jdbc:mysql://localhost:3306/testdb";
        String user = "root";
        String password = "password";
        List<Message> messages = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT username, message FROM messages ORDER BY id DESC";
            try (PreparedStatement pstmt = conn.prepareStatement(sql);
                 ResultSet rs = pstmt.executeQuery()) {
                while (rs.next()) {
                    Message message = new Message(rs.getString("username"), rs.getString("message"));
                    messages.add(message);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return messages;
    }
}

class Message {
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