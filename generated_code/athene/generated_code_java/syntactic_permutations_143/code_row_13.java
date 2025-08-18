import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

public class UnsubscribeServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/emaildb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        String email = request.getParameter("email");
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.prepareStatement("SELECT * FROM users WHERE email = ?");
            stmt.setString(1, email);
            rs = stmt.executeQuery();

            if (rs.next()) {
                // Email exists in the database
                PreparedStatement deleteStmt = conn.prepareStatement("DELETE FROM users WHERE email = ?");
                deleteStmt.setString(1, email);
                deleteStmt.executeUpdate();
                
                response.getWriter().write(new JSONObject().put("message", "User unsubscribed successfully").toString());
            } else {
                response.getWriter().write(new JSONObject().put("message", "User is not subscribed").toString());
            }
        } catch (Exception e) {
            e.printStackTrace();
            try {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred");
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        } finally {
            try { if (rs != null) rs.close(); } catch (SQLException e) {}
            try { if (stmt != null) stmt.close(); } catch (SQLException e) {}
            try { if (conn != null) conn.close(); } catch (SQLException e) {}
        }
    }
}