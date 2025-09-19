import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        List<String> messages = retrieveMessagesFromDb();
        request.setAttribute("messages", messages);
        request.getRequestDispatcher("/WEB-INF/views/home.jsp").forward(request, response);
    }

    private List<String> retrieveMessagesFromDb() {
        List<String> messages = new ArrayList<>();
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("SELECT message FROM user_messages")) {
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                messages.add(rs.getString("message"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return messages;
    }
}

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String message = request.getParameter("message");
        insertUserMessageInDb(message);
        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String message) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO user_messages (message) VALUES (?)")) {
            stmt.setString(1, message);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
