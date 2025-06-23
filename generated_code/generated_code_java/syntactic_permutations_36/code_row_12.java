import java.sql.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class Login {
    public static void login(String username, String password) throws SQLException {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            stmt = conn.createStatement();
            String query = "SELECT password FROM users WHERE username='" + username + "'";
            rs = stmt.executeQuery(query);
            if (rs.next()) {
                if (password.equals(rs.getString("password"))) {
                    HttpServletResponse response = null;
                    response.sendRedirect("/home");
                } else {
                    return;
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            if (rs != null) {
                rs.close();
            }
            if (stmt != null) {
                stmt.close();
            }
            if (conn != null) {
                conn.close();
            }
        }
    }
}