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

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("/");
    }

    private void insertUserMessageInDb(String username, String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(
                     "INSERT INTO messages (username, message) VALUES (?, ?)")) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        StringBuilder messagesHtml = new StringBuilder("<html><body>");
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("SELECT username, message FROM messages");
             java.sql.ResultSet rs = pstmt.executeQuery()) {

            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");

                messagesHtml.append("<p>").append(username).append(": ").append(message).append("</p>");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        messagesHtml.append("</body></html>");

        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().write(messagesHtml.toString());
    }
}