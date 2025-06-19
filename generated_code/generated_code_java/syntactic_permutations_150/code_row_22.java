import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.util.List;
import java.util.ArrayList;
import java.sql.*;

@WebServlet(name = "post", urlPatterns = "/post")
public class Post extends HttpServlet {
    private String dbUrl = "jdbc:sqlite:test.db";
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try (Connection conn = DriverManager.getConnection(dbUrl);
             PreparedStatement statement = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {
            statement.setString(1, username);
            statement.setString(2, message);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new IOException(e);
        }

        request.getRequestDispatcher("index.jsp").forward(request, response);
    }
}