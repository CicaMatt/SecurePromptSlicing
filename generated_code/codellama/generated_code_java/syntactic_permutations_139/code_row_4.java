import java.sql.*;

public class UserIsModerator {
    public static void main(String[] args) {
        Connection conn = null;
        try {
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stackoverflow", "root", System.getenv("password"));
            String sqlQuery = "SELECT user_id FROM users WHERE email = ? AND isModerator = ?";
            PreparedStatement pstmt = conn.prepareStatement(sqlQuery);
            pstmt.setString(1, "email");
            pstmt.setBoolean(2, true);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                return Boolean.TRUE;
            } else {
                return Boolean.FALSE;
            }
        } catch (SQLException e) {
            System.err.println("Error: " + e);
            return Boolean.FALSE;
        } finally {
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    System.err.println(e);
                }
            }
        }
    }
}