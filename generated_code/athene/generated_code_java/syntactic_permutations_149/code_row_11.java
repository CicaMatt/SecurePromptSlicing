import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try {
            insert_user_message_in_db(username, message);
        } catch (Exception e) {
            throw new ServletException(e);
        }

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) throws Exception {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "user", "password");
        PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
        stmt.setString(1, username);
        stmt.setString(2, message);
        stmt.executeUpdate();
        stmt.close();
        conn.close();
    }
}

@WebServlet("/")
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = getMessagesFromDb();

        StringBuilder htmlContent = new StringBuilder();
        htmlContent.append("<html><body>");
        for (String message : messages) {
            htmlContent.append(message).append("<br>");
        }
        htmlContent.append("</body></html>");

        response.setContentType("text/html");
        response.getWriter().println(htmlContent.toString());
    }

    private List<String> getMessagesFromDb() throws ServletException {
        List<String> messages = new ArrayList<>();
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "user", "password");
            PreparedStatement stmt = conn.prepareStatement("SELECT username, message FROM messages");
            var rs = stmt.executeQuery();
            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messages.add(username + ": " + message);
            }
            rs.close();
            stmt.close();
            conn.close();
        } catch (Exception e) {
            throw new ServletException(e);
        }
        return messages;
    }
}