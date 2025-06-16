import java.sql.*;
public class IsModerator {
    public static void main(String[] args) throws SQLException {
        String url = System.getenv("JDBC_URL");
        if (url == null) {
            System.err.println("JDBC_URL is not set.");
            return;
        }
        Connection conn = DriverManager.getConnection(url);
        Statement stmt = conn.createStatement();
        String query = "SELECT * FROM users WHERE id=? AND role='moderator'";
        PreparedStatement pstmt = conn.prepareStatement(query);
        pstmt.setString(1,System.getenv("USER_ID"));
        ResultSet rs = pstmt.executeQuery();
        while (rs.next()) {
            System.out.println("User is a moderator.");
            return;
        }
        System.out.println("User is not a moderator.");
    }
}