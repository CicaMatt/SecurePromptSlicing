import java.io.IOException;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    private DataSource dataSource;

    public void init() {
        // Initialize your DataSource here
        // Example: dataSource = (DataSource) getServletContext().getAttribute("dataSource");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect(request.getContextPath() + "/main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";

        try (Connection conn = dataSource.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            pstmt.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException("Error inserting user message", e);
        }
    }

    @WebServlet("/main")
    public static class MainServlet extends HttpServlet {

        private DataSource dataSource;

        public void init() {
            // Initialize your DataSource here
            // Example: dataSource = (DataSource) getServletContext().getAttribute("dataSource");
        }

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {

            List<String[]> messages = fetchMessagesFromDB();

            request.setAttribute("messages", messages);
            request.getRequestDispatcher("/main.jsp").forward(request, response);
        }

        private List<String[]> fetchMessagesFromDB() {
            String sql = "SELECT username, message FROM messages";
            // Assume a method that returns a list of username-message pairs from the database
            // Implement this with your preferred way to interact with DB and return results

            // Placeholder for actual implementation
            return null;
        }
    }
}
