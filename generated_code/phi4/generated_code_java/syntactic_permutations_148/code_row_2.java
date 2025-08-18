import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)")) {

            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            PreparedStatement stmt = conn.prepareStatement("SELECT username, message FROM messages");
            ResultSet rs = stmt.executeQuery();

            StringBuilder output = new StringBuilder("<html><body>");
            while (rs.next()) {
                String user = rs.getString("username");
                String msg = rs.getString("message");
                output.append("<p>").append(user).append(": ").append(msg).append("</p>");
            }
            output.append("</body></html>");

            response.setContentType("text/html");
            response.getWriter().write(output.toString());

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


**Note:** Ensure you have the necessary JDBC driver for MySQL in your classpath and replace `your_database`, `username`, and `password` with actual database details. Also, create a table named `messages` with columns `username` and `message`.