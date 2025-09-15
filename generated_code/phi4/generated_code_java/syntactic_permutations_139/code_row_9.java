import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorCheck {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String usernameToCheck = "exampleUser"; // replace with the actual user to check
        boolean isModerator = checkIfModerator(usernameToCheck);
        System.out.println("Is moderator: " + isModerator);
    }

    public static boolean checkIfModerator(String username) {
        String query = "SELECT COUNT(*) FROM users WHERE username = ? AND is_moderator = 1";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, username);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    int count = rs.getInt(1);
                    return count > 0;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return false;
    }
}
