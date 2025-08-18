import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int unsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(checkQuery)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    int count = rs.getInt(1);
                    if (count == 0) {
                        return 1;
                    } else {
                        String unsubscribeQuery = "UPDATE users SET subscribed = false WHERE email = ?";
                        try (PreparedStatement updateStmt = conn.prepareStatement(unsubscribeQuery)) {
                            updateStmt.setString(1, email);
                            int rowsAffected = updateStmt.executeUpdate();
                            if (rowsAffected > 0) {
                                return 0;
                            }
                        }
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public static void main(String[] args) {
        EmailUnsubscriber eu = new EmailUnscriber();
        System.out.println(eu.unsubscribeEmail("test@example.com"));
    }
}