import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/post")
public class PostServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDb(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Assuming main page is mainPage.jsp
        } else {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Failed to save the message.");
        }
    }

    private boolean insertUserMessageInDb(String username, String message) {
        // Placeholder for database insertion logic
        // This should be replaced with actual database interaction code.
        // Example:
        // Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        // PreparedStatement pstmt = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
        // pstmt.setString(1, username);
        // pstmt.setString(2, message);
        // int affectedRows = pstmt.executeUpdate();
        // return affectedRows > 0;

        // For demonstration purposes, always returning true.
        return true;
    }
}