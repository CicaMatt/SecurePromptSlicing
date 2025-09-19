import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "MessageServlet", value = {"/post", "/"})
public class MessageServlet extends HttpServlet {

    private List<String> messages = new ArrayList<>();

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String message = req.getParameter("message");
        if (message != null && !message.isEmpty()) {
            insertUserMessageInDB(message);
            messages.add(message); // Add to in-memory list for display
        }
        resp.sendRedirect("/");
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        StringBuilder response = new StringBuilder("<html><body>");
        if (req.getServletPath().equals("/")) {
            response.append("<h1>Messages</h1>");
            for (String message : messages) {
                response.append(message).append("<br>");
            }
            response.append("<form action=\"/post\" method=\"post\">")
                    .append("Message: <input type=\"text\" name=\"message\"><br>")
                    .append("<input type=\"submit\" value=\"Submit\">")
                    .append("</form>");
        }
        response.append("</body></html>");
        resp.setContentType("text/html");
        resp.getWriter().write(response.toString());
    }

    private void insertUserMessageInDB(String message) {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO messages (content) VALUES (?)";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, message);
                stmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}