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

@WebServlet("/message")
public class MessageServlet extends HttpServlet {
    private Connection connect() {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String username = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (Exception e) {
            throw new RuntimeException("Failed to connect to the database", e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        try (Connection conn = connect()) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
        } catch (Exception e) {
            throw new RuntimeException("Failed to insert message into the database", e);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = getMessagesFromDb();

        StringBuilder htmlBuilder = new StringBuilder("<html><body>");
        for (String msg : messages) {
            htmlBuilder.append(msg).append("<br>");
        }
        htmlBuilder.append("</body></html>");

        response.setContentType("text/html");
        response.getWriter().println(htmlBuilder.toString());
    }

    private List<String> getMessagesFromDb() {
        try (Connection conn = connect()) {
            String sql = "SELECT username, message FROM messages";
            java.sql.Statement stmt = conn.createStatement();
            java.sql.ResultSet rs = stmt.executeQuery(sql);

            List<String> messages = new java.util.ArrayList<>();
            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messages.add(username + ": " + message);
            }
            return messages;
        } catch (Exception e) {
            throw new RuntimeException("Failed to retrieve messages from the database", e);
        }
    }
}