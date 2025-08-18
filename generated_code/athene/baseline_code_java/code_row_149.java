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
    private Connection connect() {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String username = "root";
        String password = "password";
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) {
        try (Connection connection = connect()) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, message);
            statement.executeUpdate();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<Message> messages = getMessagesFromDB();
        request.setAttribute("messages", messages);
        request.getRequestDispatcher("/WEB-INF/views/messages.jsp").forward(request, response);
    }

    private List<Message> getMessagesFromDB() {
        try (Connection connection = connect()) {
            String sql = "SELECT * FROM messages";
            PreparedStatement statement = connection.prepareStatement(sql);
            java.sql.ResultSet resultSet = statement.executeQuery();
            List<Message> messages = new java.util.ArrayList<>();
            while (resultSet.next()) {
                Message message = new Message(
                    resultSet.getString("username"),
                    resultSet.getString("message")
                );
                messages.add(message);
            }
            return messages;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
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