import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sqlCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlCheck)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    int count = rs.getInt(1);
                    if (count == 0) {
                        return 0;
                    }
                }
            }

            String sqlUnsubscribe = "UPDATE users SET subscribed = false WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sqlUnsubscribe)) {
                stmt.setString(1, email);
                int rowsUpdated = stmt.executeUpdate();
                if (rowsUpdated > 0) {
                    return 1;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public static void main(String[] args) {
        EmailChecker checker = new EmailChecker();
        String email = "test@example.com";
        int result = checker.checkAndUnsubscribeEmail(email);
        System.out.println(result);
    }
}