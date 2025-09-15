import java.io.IOException;
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

@WebServlet({"/", "/post"})
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private Connection connection;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/messagesdb", "username", "password");
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            PreparedStatement statement = connection.prepareStatement("SELECT username, message FROM messages ORDER BY id DESC");
            ResultSet resultSet = statement.executeQuery();
            List<String> messages = new ArrayList<>();
            while (resultSet.next()) {
                String userMessage = resultSet.getString("username") + ": " + resultSet.getString("message");
                messages.add(userMessage);
            }
            request.setAttribute("messages", messages);
            request.getRequestDispatcher("/WEB-INF/index.jsp").forward(request, response);
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try (PreparedStatement statement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {
            statement.setString(1, username);
            statement.setString(2, message);
            statement.executeUpdate();
        } catch (Exception e) {
            throw new ServletException(e);
        }

        response.sendRedirect("/");
    }
}
