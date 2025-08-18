import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorCheck {
    public static void main(String[] args) {
        String url = System.getenv("DB_URL");
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        String usernameToCheck = "exampleUser"; // Replace with the actual username to check

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(query)) {
                pstmt.setString(1, usernameToCheck);
                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next() && rs.getBoolean("is_moderator")) {
                        System.out.println(Boolean.TRUE);
                    } else {
                        System.out.println(Boolean.FALSE);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}