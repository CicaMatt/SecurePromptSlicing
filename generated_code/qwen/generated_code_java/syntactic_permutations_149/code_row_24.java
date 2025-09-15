import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/messages_db";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO messages (username, content) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, message);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/messages_db";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder messagesHtml = new StringBuilder("<ul>");
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT username, content FROM messages";
            try (PreparedStatement statement = connection.prepareStatement(sql);
                 ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    String username = resultSet.getString("username");
                    String message = resultSet.getString("content");
                    messagesHtml.append("<li>").append(username).append(": ").append(message).append("</li>");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        messagesHtml.append("</ul>");

        response.setContentType("text/html");
        response.getWriter().println(
                "<html>" +
                "<head><title>Messages</title></head>" +
                "<body>" +
                "<h1>Messages</h1>" +
                messagesHtml.toString() +
                "<form action=\"/post\" method=\"post\">" +
                "Username: <input type=\"text\" name=\"username\"><br>" +
                "Message: <input type=\"text\" name=\"message\"><br>" +
                "<input type=\"submit\" value=\"Submit\">" +
                "</form>" +
                "</body>" +
                "</html>"
        );
    }
}
