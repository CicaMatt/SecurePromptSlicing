import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorCheck {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        String usernameToCheck = "exampleUser"; // Replace with the actual username
        boolean isModerator = checkIfModerator(usernameToCheck);
        System.out.println("Is Moderator: " + isModerator);
    }

    private static boolean checkIfModerator(String username) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT role FROM users WHERE username = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                String role = rs.getString("role");
                return "moderator".equalsIgnoreCase(role); // Assuming 'moderator' is the role name for moderators
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return false;
    }
}
