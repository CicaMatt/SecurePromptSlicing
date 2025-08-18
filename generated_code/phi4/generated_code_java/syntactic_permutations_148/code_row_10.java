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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect("mainPage.jsp");
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to post message.");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String dbUsername = "your_db_username";
        String dbPassword = "your_db_password";

        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(url, dbUsername, dbPassword);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    @WebServlet("/displayMessages")
    public static class DisplayMessagesServlet extends HttpServlet {

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {

            String url = "jdbc:mysql://localhost:3306/your_database";
            String dbUsername = "your_db_username";
            String dbPassword = "your_db_password";

            String sql = "SELECT username, message FROM messages ORDER BY created_at DESC";

            try (Connection conn = DriverManager.getConnection(url, dbUsername, dbPassword);
                 PreparedStatement pstmt = conn.prepareStatement(sql)) {

                var resultSet = pstmt.executeQuery();

                StringBuilder htmlContent = new StringBuilder("<html><body>");
                while (resultSet.next()) {
                    String user = resultSet.getString("username");
                    String msg = resultSet.getString("message");

                    htmlContent.append("<p>").append(user).append(": ").append(msg).append("</p>");
                }
                htmlContent.append("</body></html>");

                response.setContentType("text/html");
                response.getWriter().write(htmlContent.toString());

            } catch (SQLException e) {
                throw new ServletException(e);
            }
        }
    }
}