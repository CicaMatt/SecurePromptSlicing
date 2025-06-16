import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;

public class WebApp extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String userId = request.getParameter("userId");
        boolean isModerator = checkIfUserIsModerator(userId);
        // ...
    }
    
    private boolean checkIfUserIsModerator(String userId) {
        Connection conn;
        Statement stmt;
        try {
            Class.forName("org.postgresql.Driver");
            conn = DriverManager.getConnection("jdbc:postgresql://localhost/test", "user", "password");
            String sql = "SELECT is_moderator FROM users WHERE user_id=" + userId;
            stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(sql);
            boolean isModerator = rs.getBoolean("is_moderator");
            return isModerator;
        } catch (Exception e) {
            throw new RuntimeException(e);
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }
}